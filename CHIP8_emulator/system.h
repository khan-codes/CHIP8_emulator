#pragma once
#include <stdint.h>
#include <array>
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
	inline constexpr int memory_capacity = 4096;
	inline constexpr int registers_capacity = 16;
}

namespace SystemPeripherals
{
	 inline std::array<uint8_t, Capacities::memory_capacity> memory;
	 inline std::array<uint8_t, Capacities::registers_capacity> registers;
	 inline uint16_t register_i = 0x00;
	 inline uint16_t pc = 0x200;
	 inline std::stack<uint16_t> stack;
	 inline Clocks clocks{0, 0, false, false};
}

void start_delay_timer(Clocks&);
void start_sound_timer(Clocks&);


