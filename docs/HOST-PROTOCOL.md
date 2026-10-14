# Driving the board from your own host

**English** | [Français](HOST-PROTOCOL.fr.md)

This page is for anyone who wants to run Daytona USA on their own computer (PC, single-board computer, their own emulator
build) and use this board to reach the cabinet. It covers everything that crosses the USB cable between the host and the
Arduino Mega, and what the host has to do with it.

## 1. How it works

The Mega does no game logic. It's a bridge that carries the **raw port bytes of the original 837-10539 I/O board**:

- **Mega → host, every 1 ms:** the switches, the shifter, the three potentiometers and the drive board's reply, exactly as the
  original I/O board would see them on its pins.
- **Host → Mega:** two bytes, the drive board command and the lamps/meters, which the Mega copies straight to its output ports.

So the host has to **emulate the I/O board itself**, then connect that emulated board's ports to the Mega instead of a
keyboard or joystick. MAME already emulates this board (`model1io`, which runs the real Sega I/O board ROM), so the game
sees exactly what it saw in the original cabinet: the ROM decides when a lamp lights, when a meter counts and what goes to
the drive board.

```
cabinet switches, pots, drive board  ──>  Mega  ──USB──>  host: emulated I/O board  ──>  game
lamps, meters, drive board           <──  Mega  <──USB──  host: emulated I/O board  <──  game
```

## 2. Getting started

1. Flash the Mega with [`firmware/m2io-mega`](../firmware/m2io-mega) (Arduino IDE, or `arduino-cli`):

   ```bash
   arduino-cli compile --fqbn arduino:avr:mega firmware/m2io-mega
   arduino-cli upload --fqbn arduino:avr:mega -p /dev/ttyACM0 firmware/m2io-mega
   ```

2. Check the board without any emulator, using [`tools/m2io_console.py`](../tools/m2io_console.py) (Python 3 + pyserial). It
   prints every input live and can light lamps or send a drive board command:

   ```bash
   python3 tools/m2io_console.py /dev/ttyACM0
   ```

   Press each cabinet button, move the shifter, wheel and pedals: each one should show up. Then try `--chase` (lamps in
   turn, meters left alone).

3. Optional: [`firmware/test/host_test.cpp`](../firmware/test/host_test.cpp) runs the Mega program on a PC, without a Mega
   (`c++ -std=c++17 -o host_test firmware/test/host_test.cpp && ./host_test`).

[`firmware/m2io-mega/m2io_proto.h`](../firmware/m2io-mega/m2io_proto.h) is plain C++ with no Arduino dependency: a C++ host
can include it as is to build and decode frames.

## 3. Serial link

| | |
|---|---|
| Port | the Mega's USB port: `/dev/ttyACM0` on Linux (genuine Mega), `/dev/ttyUSB0` (CH340 clones), `/dev/cu.usbmodem…` on macOS, `COMx` on Windows |
| Settings | **250 000 baud**, 8N1, no flow control |

**Opening the port resets the Mega** (DTR), like any Arduino:

- In the first ~5 ms, 10 to 25 **stale frames** left over from the previous session arrive. Drop everything received in the
  first **300 ms**.
- The bootloader runs next. The first real frame arrives about **0.9 s** after the port opens, with the sequence counter
  starting from 0.
- **Send nothing before that first real frame.** The bootloader takes any byte it receives for the start of an upload and
  never starts the program.

## 4. Frames

| Direction | Length | Bytes |
|---|---|---|
| Mega → host, every 1 ms | 9 | `A5`, sequence, IN0, IN1, drive board reply, steering, accelerator, brake, checksum |
| Host → Mega | 4 | `5A`, drive board command, lamps, checksum |

- **Checksum:** chosen so that the sum of **all** the bytes of the frame, header included, is 0 modulo 256
  (`checksum = (0x100 - sum of the previous bytes) & 0xFF`).
- **Sequence:** goes up by 1 per frame and wraps at 255, so a gap shows a lost frame.
- **Receiving:** use a sliding window. Push each byte in; once the window holds 9 bytes, starts with `A5` and sums to 0, you
  have a frame. After a lost or damaged byte, this falls back into step by itself (`m2io::Receiver` in `m2io_proto.h`).
- **Sending:** send a command frame whenever the drive or lamps byte changes, and **at least once every 16 ms** even if
  nothing changed.
- **Watchdog:** if the Mega gets no valid frame for **200 ms**, it sends `00` to the drive board, switches off every lamp and
  stops the meters. This is also the state of its outputs at power-up.

## 5. What each byte means

Bits marked "active low" read 0 when the switch is pressed.

| Byte | Bits |
|---|---|
| **IN0** | 0 coin 1 · 1 coin 2 · 2 TEST · 3 SERVICE · 4 START · 5 VR1 · 6 VR2 · 7 VR3 (all active low) |
| **IN1** | 0 VR4 (active low) · 1 screen jumper JP8, see below · 2-3 not wired, read as 1 · 4-6 shifter contacts · 7 4th shifter contact |
| **Drive board reply** | the 8 lines coming back from the drive board (I/O board port E, read) |
| **Steering, accelerator, brake** | the potentiometers, 0-255 (10-bit ADC divided by 4, like the I/O board's 8-bit MSM6253) |
| **Drive board command** | the 8 lines to the drive board (I/O board port E, write). `00` = motor off |
| **Lamps** | 0 coin meter 1 · 1 coin meter 2 · 2 START · 3 VR1 · 4 VR2 · 5 VR3 · 6 VR4 · 7 leader (1 = on) |

- **Lamps bits 0-1 drive the original coin meters:** every pulse adds one coin to a mechanical counter. Don't use them for
  testing.
- **JP8** (V2 board) ties the Mega's D36 to ground. IN1 bit 1 reads **0 when the jumper is fitted** and 1 when it's removed.
  It's not a game input: it's there so the host can choose its screen at start-up (fitted = CRT 4:3 through an HDMI-to-VGA
  adapter, removed = LVDS 16:9). How the host uses it is up to the host. Before you hand IN1 to the I/O board, set bit 1 to 1:
  bits 1-3 aren't used by Daytona (MAME marks them unused) and read 1 on the original board.
- **The shifter is passed raw.** The cabinet's own contacts produce the gear code the game expects, so don't convert it.
  MAME's `daytona_gearbox_r` only exists to build that code from keys.

## 6. Connecting it to an emulated I/O board

Each byte goes to one port of the I/O board's 315-5338A chip or to its MSM6253 ADC. In MAME, the `model1io` device already
has a callback for each one (`src/mame/sega/model1io.h`):

| Byte | I/O board port | MAME `model1io` callback | How MAME binds it for Daytona today |
|---|---|---|---|
| IN0 | 315-5338A port B (read) | `in_callback<0>` | ioport `IN0` |
| IN1 | 315-5338A port C (read) | `in_callback<1>` | ioport `IN1` (gearbox from keys) |
| Steering, accelerator, brake | MSM6253 channels 0-2 | `an_callback<0>` to `<2>` | ioports `STEER`, `ACCEL`, `BRAKE` |
| Drive board reply | 315-5338A port E (read) | `drive_read_callback` | not bound: reads `0xFF` |
| Drive board command | 315-5338A port E (write) | `drive_write_callback` | `drive_board_w`, to the emulated drive board CPU |
| Lamps | 315-5338A port F (write) | `output_callback` | `lamp_output_w` (coin counters, lamp outputs) |

The last column describes MAME master as of 2026-10 (commit `74b9fae`), in `model2o_state::daytona()` and `model2o()` in
`src/mame/sega/model2.cpp`.

**Force feedback needs a modified emulator.** In stock MAME, the drive board command goes to an emulated drive board CPU,
but that CPU's motor output isn't connected to anything (`driveio_port_w` is marked TODO). Nothing leaves MAME that could
drive the real motor. With this board, the cabinet's **real** drive board does the work, so `drive_write_callback` must send
the command to the Mega and `drive_read_callback` must return the Mega's reply. The emulated drive board is then no longer
needed.

**Lamps and inputs** go through the same callbacks. Rebind the five other callbacks so they read and write the latest values
exchanged with the Mega.

## 7. What your host has to do

1. Open the port at 250 000 baud. Drop everything for 300 ms, then wait for the first valid frame before sending anything.
2. Read frames on their own thread, at 1 kHz. Keep the latest IN0, IN1, potentiometers and drive reply where the emulation
   thread can read them.
3. **Debounce IN0 and IN1 bit 0** (coin, START, VR, TEST, SERVICE). A press counts at once; a release counts only once the
   bit has stayed at 1 for about **25 consecutive frames** (25 ms).
   - Switches bounce for up to about 60 ms. Without this filter, one coin can count twice.
   - The filter also stretches every press past one game frame (about 17 ms), so a short coin pulse can't fall between two
     reads.
4. Feed the emulated I/O board from those values (§ 6), with IN1 bit 1 forced to 1.
5. Each time the emulated board writes port E or port F, send `5A, command, lamps, checksum`. Also resend at least every
   16 ms.
6. **Stop sending while the emulation is paused or frozen.** The Mega then puts the drive board and the lamps in the safe
   state 200 ms later, instead of leaving a force or a lamp stuck on.
7. If no frame has arrived for about 100 ms, treat the link as lost: report every switch released, the potentiometers at
   rest and the drive reply as `0xFF`. If the Mega was unplugged, reopen the port.
8. On exit, send `5A 00 00 A6` (motor off, everything off), then close the port.

## 8. Precautions with a real drive board

- **Hands off the wheel the first time.** `00`, the command the Mega sends at power-up and after the watchdog, is motor off
  according to the drive board ROM (EPR-16488A).
- **Drive board lines during the reset:** for the ~0.9 s the Mega spends in its bootloader after the port opens, its drive
  board outputs aren't driven, and the board has no resistors on those lines. Open the port once, when the host starts, and
  keep it open.
