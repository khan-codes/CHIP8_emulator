#include <iostream>
#include <vector>
#include <bitset>
#include "utility.h"

int main()
{
	std::vector<uint8_t> hex_data = read_hex_file("F:/projects/CHIP8_emulator/CHIP8_emulator/resources/1-chip8-logo.ch8");
	traverse_rom(hex_data);

	return 0;
}