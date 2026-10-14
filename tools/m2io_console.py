#!/usr/bin/env python3
"""Test console for the M2 IO Emulator Board: plays the host's part from any computer (Python 3 + pyserial).

Shows what the Mega sends (switches, shifter, screen jumper JP8, potentiometers, drive board reply) and can send it a
drive board command and a lamps byte. Protocol: docs/HOST-PROTOCOL.md and firmware/m2io-mega/m2io_proto.h.

  python3 m2io_console.py /dev/ttyACM0                     # read only (the Mega keeps its outputs in the safe state)
  python3 m2io_console.py /dev/ttyACM0 --lamps 0x04        # START lamp on
  python3 m2io_console.py /dev/ttyACM0 --chase             # START, VR1-VR4, leader lamps in turn (not the meters)
  python3 m2io_console.py /dev/ttyACM0 --drive 0x00        # drive board command (0x00 = motor off)
  python3 m2io_console.py --replay stream.bin              # decode a file (decoder test)

Opening the port resets the Mega (DTR): about 0.9 s of bootloader before the first frames. Nothing is sent before the
first frame after that reset: the bootloader takes any byte it receives for the start of an upload and never starts the
program (measured: commands sent from the moment the port opens, 0 frames in 4 s; nothing sent, first frame at 0.90 s).
Frames from the first 0.3 s (left over from the previous session) are dropped.
Lamp bits 0-1 drive the original coin meters: every pulse adds one coin to the meter.
"""
import argparse, sys, time

STATE_HDR, CMD_HDR, STATE_LEN, CMD_LEN, BAUD = 0xA5, 0x5A, 9, 4, 250000
BOOT_IGNORE = 0.3   # s: stale frames from before the Mega reset
IN0 = ['COIN1', 'COIN2', 'TEST', 'SERVICE', 'START', 'VR1', 'VR2', 'VR3']
LEVER = {4: '1/3', 5: '2/4', 6: '1-2/3-4', 7: '4th'}


def checksum(b):
    return (0x100 - sum(b)) & 0xFF


def encode_cmd(drive, lamps):
    f = bytes([CMD_HDR, drive & 0xFF, lamps & 0xFF])
    return f + bytes([checksum(f)])


class StateReceiver:
    """Same sliding window as m2io::Receiver."""
    def __init__(self):
        self.win = bytearray()

    def push(self, b):
        self.win.append(b)
        if len(self.win) > STATE_LEN:
            del self.win[0]
        if len(self.win) == STATE_LEN and self.win[0] == STATE_HDR and sum(self.win) & 0xFF == 0:
            f = bytes(self.win)
            self.win.clear()
            return dict(seq=f[1], in0=f[2], in1=f[3], drive_reply=f[4], steer=f[5], accel=f[6], brake=f[7])
        return None


def describe(s):
    pressed = [n for i, n in enumerate(IN0) if not s['in0'] >> i & 1]
    if not s['in1'] & 1:
        pressed.append('VR4')
    lever = [n for i, n in LEVER.items() if not s['in1'] >> i & 1]
    screen = 'ON' if not s['in1'] & 2 else 'OFF'   # screen jumper JP8 (V2 board), D36 = bit 1
    return ('IN0=%02X IN1=%02X  pressed: %-28s shifter: %-14s  JP8 %-3s  steer %3d  accel %3d  brake %3d  drive> %02X'
            % (s['in0'], s['in1'], ' '.join(pressed) or '-', ' '.join(lever) or '-', screen,
               s['steer'], s['accel'], s['brake'], s['drive_reply']))


def replay(path):
    rx, n = StateReceiver(), 0
    for b in open(path, 'rb').read():
        s = rx.push(b)
        if s:
            n += 1
            print('seq %3d  %s' % (s['seq'], describe(s)))
    print('%d frame(s)' % n)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('port', nargs='?')
    ap.add_argument('--replay')
    ap.add_argument('--drive', type=lambda x: int(x, 0))
    ap.add_argument('--lamps', type=lambda x: int(x, 0))
    ap.add_argument('--chase', action='store_true')
    a = ap.parse_args()
    if a.replay:
        return replay(a.replay)
    if not a.port:
        ap.error('serial port missing')
    import serial   # pyserial
    send = a.drive is not None or a.lamps is not None or a.chase
    drive = a.drive if a.drive is not None else 0x00
    lamps = a.lamps if a.lamps is not None else 0x00
    ser = serial.Serial(a.port, BAUD, timeout=0.01)
    rx = StateReceiver()
    last_seq, frames, lost, t_print, t_send, t0 = None, 0, 0, 0, 0, time.monotonic()
    booted = False   # first frame after the Mega reset received
    try:
        while True:
            now = time.monotonic()
            if a.chase:
                lamps = 1 << (2 + int((now - t0) / 0.5) % 6)   # bits 2-7: START, VR1-VR4, leader
            if send and booted and now - t_send >= 0.016:   # like the game: once per video frame
                ser.write(encode_cmd(drive, lamps))
                t_send = now
            for b in ser.read(256):
                s = rx.push(b)
                if not s:
                    continue
                if now - t0 < BOOT_IGNORE:
                    continue
                if not booted:
                    booted, t_boot = True, now   # rate counted from the reset
                frames += 1
                if last_seq is not None:
                    lost += (s['seq'] - last_seq - 1) & 0xFF
                last_seq = s['seq']
                if now - t_print >= 0.1:
                    rate = frames / max(now - t_boot, 1e-3)
                    out = ' command %02X lamps %02X' % (drive, lamps) if send else ''
                    sys.stdout.write('\r%s  %4.0f fr/s lost %d%s ' % (describe(s), rate, lost, out))
                    sys.stdout.flush()
                    t_print = now
    except KeyboardInterrupt:
        print()
    finally:
        ser.close()


if __name__ == '__main__':
    main()
