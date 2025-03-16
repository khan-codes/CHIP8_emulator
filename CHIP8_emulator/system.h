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
	extern int memory_capacity;
	extern int registers_capacity;
}

namespace SystemPeripherals
{
	extern std::vector<uint8_t> memory;
	extern std::vector<uint16_t> registers;
	extern std::stack<uint16_t> stack;
	extern Clocks clocks;
}

void start_delay_timer(Clocks&);
void start_sound_timer(Clocks&);


