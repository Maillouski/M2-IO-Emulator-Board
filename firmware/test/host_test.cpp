// PC test of the Mega program (m2io-mega.ino) and of the protocol (m2io_proto.h), without a Mega.
// The .ino is compiled as is against a minimal Arduino imitation: ports, Serial, millis/micros, analogRead.
//
//   c++ -std=c++17 -Wall -Wextra -O1 -o host_test host_test.cpp && ./host_test [file.bin]
// With a file: writes a Mega -> host test stream to it (to check the Python decoder of tools/m2io_console.py).

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <deque>
#include <vector>

// ---- Arduino imitation ----
static uint8_t PORTA, DDRA, PORTK, DDRK, PORTL, DDRL, PORTC, DDRC, PORTB, DDRB;
static uint8_t PINL = 0xff, PINC = 0xff, PINB = 0xff;
static uint32_t sim_us;
static uint16_t adc[3] = { 512, 128, 1023 };
enum { A0 = 54, A1, A2 };
static uint32_t micros() { return sim_us; }
static uint32_t millis() { return sim_us / 1000; }
static int analogRead(int pin) { sim_us += 112; return adc[pin - A0]; }   // one conversion at 125 kHz

struct FakeSerial {
	std::deque<uint8_t> rx;
	std::vector<uint8_t> tx;
	uint32_t baud = 0;
	void begin(uint32_t b) { baud = b; }
	int available() { return int(rx.size()); }
	int read() { int b = rx.front(); rx.pop_front(); return b; }
	int availableForWrite() { return 63; }
	size_t write(const uint8_t *b, size_t n) { tx.insert(tx.end(), b, b + n); return n; }
} Serial;

#include "../m2io-mega/m2io-mega.ino"

// ---- test helpers ----
static int failures;
#define CHECK(c) do { if (!(c)) { printf("FAIL line %d: %s\n", __LINE__, #c); failures++; } } while (0)

static void run_us(uint32_t us)
{
	uint32_t end = sim_us + us;
	while (int32_t(sim_us - end) < 0) {
		loop();
		sim_us += 20;   // cost of an idle loop pass (order of magnitude)
	}
}

static void send_cmd(uint8_t drive, uint8_t lamps)
{
	uint8_t f[CMD_LEN];
	encode_cmd(Cmd{ drive, lamps }, f);
	Serial.rx.insert(Serial.rx.end(), f, f + CMD_LEN);
}

static std::vector<State> decode_tx()
{
	std::vector<State> out;
	StateReceiver r;
	for (uint8_t b : Serial.tx)
		if (r.push(b)) {
			State s;
			decode_state(r.frame, s);
			out.push_back(s);
		}
	return out;
}

int main(int argc, char **argv)
{
	// 1. Start-up: outputs in the safe state, inputs with pull-ups
	setup();
	CHECK(Serial.baud == 250000);
	CHECK(DDRA == 0xff && PORTA == 0x00);
	CHECK(DDRK == 0xff && PORTK == 0x00);
	CHECK(DDRL == 0x00 && PORTL == 0xff);
	CHECK(DDRC == 0x00 && PORTC == 0xff);
	CHECK(DDRB == 0x00 && PORTB == 0x00);

	// 2. One frame per ms, content = raw ports and 8-bit ADC
	PINL = 0xfe;   // coin 1 pressed
	PINC = 0xbf;   // shifter, bit 6 low
	PINB = 0x5a;
	run_us(100000);
	std::vector<State> st = decode_tx();
	printf("frames in 100 ms: %zu\n", st.size());
	CHECK(st.size() >= 99 && st.size() <= 101);
	CHECK(Serial.tx.size() == st.size() * STATE_LEN);   // no extra byte
	bool seq_ok = true;
	for (size_t i = 1; i < st.size(); i++)
		seq_ok &= uint8_t(st[i].seq) == uint8_t(st[i - 1].seq + 1);
	CHECK(seq_ok);
	CHECK(st.back().in0 == 0xfe && st.back().in1 == 0xbf && st.back().drive_reply == 0x5a);
	CHECK(st.back().analog[0] == 128 && st.back().analog[1] == 32 && st.back().analog[2] == 255);

	// 3. Host commands applied; damaged or shifted frames ignored, resync by itself
	send_cmd(0x3a, 0x84);
	run_us(2000);
	CHECK(PORTA == 0x3a && PORTK == 0x84);
	uint8_t bad[CMD_LEN];
	encode_cmd(Cmd{ 0x55, 0xff }, bad);
	bad[2] ^= 0x10;                                   // one damaged bit
	Serial.rx.insert(Serial.rx.end(), { 0x00, 0x5a, 0x12 });   // junk, including a false header
	Serial.rx.insert(Serial.rx.end(), bad, bad + CMD_LEN);
	run_us(2000);
	CHECK(PORTA == 0x3a && PORTK == 0x84);
	send_cmd(0x60, 0x04);
	run_us(2000);
	CHECK(PORTA == 0x60 && PORTK == 0x04);

	// 4. Frame received byte by byte over several loop passes
	uint8_t f[CMD_LEN];
	encode_cmd(Cmd{ 0x27, 0x10 }, f);
	for (uint8_t b : f) {
		Serial.rx.push_back(b);
		run_us(300);
	}
	CHECK(PORTA == 0x27 && PORTK == 0x10);

	// 5. Watchdog: host sends every 17 ms -> nothing changes; host goes silent -> safe state after 200 ms
	for (int i = 0; i < 30; i++) {
		send_cmd(0x52, 0x01);
		run_us(17400);
	}
	CHECK(PORTA == 0x52 && PORTK == 0x01);
	run_us(210000);                                   // ~227 ms since the last frame
	CHECK(PORTA == DRIVE_NEUTRAL && PORTK == LAMPS_OFF);
	send_cmd(0x52, 0x01);                             // link comes back
	run_us(2000);
	CHECK(PORTA == 0x52 && PORTK == 0x01);

	// 5b. Exact watchdog threshold: still on at 195 ms, off at 205 ms
	send_cmd(0x11, 0x22);
	run_us(1000);
	run_us(194000);
	CHECK(PORTA == 0x11 && PORTK == 0x22);
	run_us(10000);
	CHECK(PORTA == DRIVE_NEUTRAL && PORTK == LAMPS_OFF);

	// 6. Protocol alone: random stream with frames slipped in, all found again
	srand(12345);
	std::vector<uint8_t> stream;
	std::vector<State> sent;
	for (int i = 0; i < 20000; i++) {
		int junk = rand() % 4;
		for (int j = 0; j < junk; j++)
			stream.push_back(uint8_t(rand() & 0x7f));   // junk without 0xA5 (bit 7 low)
		State s{ uint8_t(i), uint8_t(rand()), uint8_t(rand()), uint8_t(rand()),
			{ uint8_t(rand()), uint8_t(rand()), uint8_t(rand()) } };
		uint8_t g[STATE_LEN];
		encode_state(s, g);
		stream.insert(stream.end(), g, g + STATE_LEN);
		sent.push_back(s);
	}
	StateReceiver r;
	size_t found = 0, match = 0;
	for (uint8_t b : stream)
		if (r.push(b)) {
			State s;
			decode_state(r.frame, s);
			if (found < sent.size() && s.seq == sent[found].seq && s.in0 == sent[found].in0
			    && s.analog[2] == sent[found].analog[2])
				match++;
			found++;
		}
	printf("random stream: %zu frames sent, %zu received, %zu identical\n", sent.size(), found, match);
	CHECK(found == sent.size() && match == sent.size());

	if (argc > 1) {
		FILE *o = fopen(argv[1], "wb");
		std::vector<uint8_t> v = { 0x13, 0xa5, 0x00 };   // leading junk, including a false header
		uint8_t g[STATE_LEN];
		encode_state(State{ 7, 0xfe, 0x8e, 0xff, { 0x80, 0x20, 0x20 } }, g);
		v.insert(v.end(), g, g + STATE_LEN);
		encode_state(State{ 8, 0xef, 0xbe, 0x3c, { 0x01, 0xfe, 0x99 } }, g);
		v.insert(v.end(), g, g + STATE_LEN);
		fwrite(v.data(), 1, v.size(), o);
		fclose(o);
	}

	printf(failures ? "%d FAILURE(S)\n" : "all pass\n", failures);
	return failures != 0;
}
