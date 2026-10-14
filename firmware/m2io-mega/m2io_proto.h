// Serial protocol between the Arduino Mega of the M2 IO Emulator Board and the host (the computer running the game).
// Documented in docs/HOST-PROTOCOL.md.
//
// Plain C++, no Arduino dependency: shared by the Mega program, the PC test and any host written in C++.
//
// Mega -> host, every 1 ms, 9 bytes:
//   A5, sequence, IN0, IN1, drive board reply, steering, accelerator, brake, checksum
// Host -> Mega, on every change and at least once per video frame, 4 bytes:
//   5A, drive board command, lamps, checksum
// Checksum: chosen so that the sum of ALL bytes of the frame (header included) is 0 modulo 256.
//
// Raw bytes, in the pin order of the 837-10539 I/O board:
//   IN0 = Mega port L (D49..D42): coin 1, coin 2, TEST, SERVICE, START, VR1, VR2, VR3; active low
//   IN1 = port C (D37..D30): bit 0 VR4 (active low), bit 1 screen jumper JP8 (D36, V2 board, 0 = fitted),
//         bits 2-3 not wired (1), bits 4-6 shifter, bit 7 4th shifter contact
//   drive board reply = port B (D53, D52, D51, D50, D10..D13) = I/O board port E, read
//   drive board command = port A (D22..D29) = I/O board port E, write
//   lamps = port K (A8..A15) = I/O board port F: meter 1, meter 2, START, VR1-VR4, leader
//   steering, accelerator, brake = A0, A1, A2 on 8 bits (like the I/O board's MSM6253)
#pragma once
#include <stdint.h>
#include <string.h>

namespace m2io {

const uint32_t BAUD = 250000;           // exact at 16 MHz (U2X), accepted by the Mega's 16U2 and by a CH340
const uint8_t STATE_HDR = 0xA5;         // Mega -> host
const uint8_t CMD_HDR = 0x5A;           // host -> Mega
const uint8_t STATE_LEN = 9;
const uint8_t CMD_LEN = 4;
const uint8_t DRIVE_NEUTRAL = 0x00;     // 0x0X with X & 7 < 5 and X != A: motor off (read from the drive board ROM
                                        // EPR-16488A; not measured on a real drive board)
const uint8_t LAMPS_OFF = 0x00;
const uint16_t LINK_TIMEOUT_MS = 200;   // no valid frame from the host: neutral command, lamps and meters off

struct State {
	uint8_t seq;
	uint8_t in0;
	uint8_t in1;
	uint8_t drive_reply;
	uint8_t analog[3];   // steering, accelerator, brake
};

struct Cmd {
	uint8_t drive;
	uint8_t lamps;
};

inline uint8_t checksum(const uint8_t *b, uint8_t n)
{
	uint8_t s = 0;
	for (uint8_t i = 0; i < n; i++)
		s += b[i];
	return uint8_t(0x100 - s);
}

inline void encode_state(const State &s, uint8_t out[STATE_LEN])
{
	out[0] = STATE_HDR;
	out[1] = s.seq;
	out[2] = s.in0;
	out[3] = s.in1;
	out[4] = s.drive_reply;
	out[5] = s.analog[0];
	out[6] = s.analog[1];
	out[7] = s.analog[2];
	out[8] = checksum(out, STATE_LEN - 1);
}

inline void decode_state(const uint8_t f[STATE_LEN], State &s)
{
	s.seq = f[1];
	s.in0 = f[2];
	s.in1 = f[3];
	s.drive_reply = f[4];
	s.analog[0] = f[5];
	s.analog[1] = f[6];
	s.analog[2] = f[7];
}

inline void encode_cmd(const Cmd &c, uint8_t out[CMD_LEN])
{
	out[0] = CMD_HDR;
	out[1] = c.drive;
	out[2] = c.lamps;
	out[3] = checksum(out, CMD_LEN - 1);
}

inline void decode_cmd(const uint8_t f[CMD_LEN], Cmd &c)
{
	c.drive = f[1];
	c.lamps = f[2];
}

// Sliding-window receiver: every byte received shifts the window; a frame is accepted when the window starts with the
// header and its sum is 0. After a lost or damaged byte, it falls back into step by itself.
template <uint8_t N, uint8_t HDR>
struct Receiver {
	uint8_t frame[N];
	uint8_t fill = 0;

	// true when frame[] holds a valid frame (read it before pushing the next byte)
	bool push(uint8_t b)
	{
		if (fill < N) {
			frame[fill++] = b;
		} else {
			memmove(frame, frame + 1, N - 1);
			frame[N - 1] = b;
		}
		if (fill < N || frame[0] != HDR)
			return false;
		uint8_t s = 0;
		for (uint8_t i = 0; i < N; i++)
			s += frame[i];
		if (s != 0)
			return false;
		fill = 0;   // frame consumed: the next one starts from scratch
		return true;
	}
};

typedef Receiver<STATE_LEN, STATE_HDR> StateReceiver;
typedef Receiver<CMD_LEN, CMD_HDR> CmdReceiver;

} // namespace m2io
