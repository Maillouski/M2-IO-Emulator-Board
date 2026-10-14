// Arduino Mega 2560 program of the M2 IO Emulator Board.
//
// No game logic: the Mega reads the switches, the drive board reply and the 3 potentiometers, sends them to the host
// every 1 ms, and copies to its ports the two bytes the host sends back (drive board command, lamps and meters). The
// host keeps all the logic of the 837-10539 I/O board. Protocol: m2io_proto.h and docs/HOST-PROTOCOL.md.
//
//   arduino-cli compile --fqbn arduino:avr:mega m2io-mega
//   arduino-cli upload  --fqbn arduino:avr:mega -p /dev/ttyACM0 m2io-mega

#include "m2io_proto.h"

using namespace m2io;

static CmdReceiver rx;
static uint32_t last_cmd_ms;
static bool link_up;
static uint8_t seq;
static uint32_t next_us;

static void outputs_safe()
{
	PORTA = DRIVE_NEUTRAL;
	PORTK = LAMPS_OFF;
}

void setup()
{
	// Outputs first: value before direction, so nothing but the safe state ever reaches the pins.
	outputs_safe();
	DDRA = 0xff;               // D22-D29: drive board command (direct wires to J5)
	DDRK = 0xff;               // A8-A15: ULN2803A inputs (U1)

	DDRL = 0x00;               // D42-D49: switches; 4.7 kΩ pull-ups on the board, internal pull-ups as well
	PORTL = 0xff;
	DDRC = 0x00;               // D30-D37: VR4, shifter; D34-D36 are not wired (D36 = JP8 on V2): internal pull-ups -> read as 1
	PORTC = 0xff;
	DDRB = 0x00;               // D50-D53, D10-D13: drive board reply; 10 kΩ pull-ups on the board
	PORTB = 0x00;

	Serial.begin(BAUD);
	next_us = micros();
}

void loop()
{
	while (Serial.available()) {
		if (rx.push(uint8_t(Serial.read()))) {
			Cmd c;
			decode_cmd(rx.frame, c);
			PORTA = c.drive;
			PORTK = c.lamps;
			last_cmd_ms = millis();
			link_up = true;
		}
	}

	// Host silent: never leave a 6 V meter energised or a force command stuck
	if (link_up && millis() - last_cmd_ms > LINK_TIMEOUT_MS) {
		outputs_safe();
		link_up = false;
	}

	uint32_t now = micros();
	if (int32_t(now - next_us) < 0)
		return;
	next_us += 1000;
	if (int32_t(now - next_us) >= 0)   // more than one period late: restart from now
		next_us = now + 1000;

	State s;
	s.seq = seq++;
	s.in0 = PINL;                      // the three ports read at the same moment
	s.in1 = PINC;
	s.drive_reply = PINB;
	s.analog[0] = uint8_t(analogRead(A0) >> 2);   // 10 bits -> 8 bits, like the MSM6253
	s.analog[1] = uint8_t(analogRead(A1) >> 2);
	s.analog[2] = uint8_t(analogRead(A2) >> 2);

	uint8_t f[STATE_LEN];
	encode_state(s, f);
	if (Serial.availableForWrite() >= STATE_LEN)   // never block the loop on sending
		Serial.write(f, STATE_LEN);
}
