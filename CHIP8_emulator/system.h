#pragma once
#include <stdint.h>
#include <vector>
#include <stack>

struct Clocks
{
	float delay_timer;
	float sound_timer;

	bool dalay_switch;
	bool sound_switch;
};

namespace Capacities
{
	extern int memory_capacity = 1024 * 4;
	extern int registers_capacity = 16;
}

namespace SystemPeripherals
{
	extern std::vector<uint8_t> memory = []() { std::vector<uint8_t> memory; memory.reserve(Capacities::memory_capacity); return memory; }();
	extern std::vector<uint16_t> registers = []() { std::vector<uint16_t> registers; registers.reserve(Capacities::registers_capacity); return registers; }();
	extern std::stack<uint16_t> stack;
	extern Clocks clocks;
}

void start_delay_timer(Clocks&);
void start_sound_timer(Clocks&);


