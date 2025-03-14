#include <filesystem>
#include <fstream>
#include <iostream>
#include "utility.h"

std::vector<uint8_t> read_hex_file(const char* filepath)
{
	std::fstream file;
	file.open(filepath, std::fstream::in|std::ios::binary);
	int file_size = (int)std::filesystem::file_size(filepath);
	std::vector<uint8_t> hex_data;
	uint8_t b;
	while (file)
	{
		file >> std::hex >> b;
		hex_data.push_back(b);
		//printf("%.2X  ", b);
	}
	file.clear();
	file.close();

	return hex_data;
}

void disassember(std::vector<uint8_t> &hex_data, int& pc)
{
	if (pc >= hex_data.size()-1) 
		return;

	// Chip8 programs start at the memory location 0x200. Catering for this.
	//pc -= 0x200;
	uint8_t hex_value = hex_data[pc];
	uint8_t firstnib = (hex_value >> 4);
	std::cout << std::format("\n{:#06x}  {:#04x}  {:#04x}", (pc), hex_value, hex_data[pc+1]);
	std::cout << "\nFirst Nibble: " << std::format("{:#01x}\n", firstnib);


	switch (firstnib)
	{
	case 0x00: std::cout << "\nclear the display"; break;
	case 0x01: 
	{
		// 1NNN: jump to instruction NNN
		uint16_t nnn = ((hex_value << 4) << 8) | (hex_data[pc + 1]<<4);
		// TODO: add 0x200 to the pc
		pc = nnn;
		std::cout << "\nnnn: " << std::format("{:#04x}\n", nnn);
		break;
	}
	case 0x02: 
	{
		// 2NNN: Execute subroutine starting at address NNN
		uint16_t nnn = ((hex_value << 4) << 8) | (hex_data[pc + 1]<<4);
		std::cout << "\nnnn: " << std::format("{:#04x}\n", nnn);
		// TODO: some stack operations required
		break;
	}
	case 0x03: 
	{
		// 3XNN: Skip the following instruction if the value of register VX equals NN
		uint8_t register_x{};	// in the array of registers search for secondnib
		if (register_x == hex_data[pc + 1])
			pc += 2;
		break;
	}
	case 0x04: 
	{
		// 4XNN	Skip the following instruction if the value of register VX is not equal to NN
		uint8_t register_x{};  // in the array of registers search for secondnib
		if (register_x != hex_data[pc + 1])
			pc += 2;
		break;
	}
	case 0x05: 
	{
		// 5XY0	Skip the following instruction if the value of register VX is equal to the value of register VY
		uint8_t register_x{};  // get the values of the resgister using the second nibble
		uint8_t register_y{};
		if (register_x == register_y)
			pc += 2;
		break;
	}
	case 0x06: 
	{
		// 6XNN	Store number NN in register VX
		// Pseudo: 
		// registers[secondnib] = hex_data[pc+1]
		break;
	}
	case 0x07: std::cout << "\nN/A "; break;
	case 0x08: std::cout << "\nN/A "; break;
	case 0x09: std::cout << "\nN/A "; break;
	case 0x0a: std::cout << "\nN/A "; break;
	case 0x0b: std::cout << "\nN/A "; break;
	case 0x0c: std::cout << "\nN/A "; break;
	case 0x0d: std::cout << "\nN/A "; break;
	case 0x0e: std::cout << "\nN/A "; break;
	case 0x0f: std::cout << "\nN/A "; break;
	case 0x10: std::cout << "\nN/A "; break;
	case 0x11: std::cout << "\nN/A "; break;
	case 0x12: std::cout << "\nN/A "; break;
	case 0x13: std::cout << "\nN/A "; break;
	case 0x14: std::cout << "\nN/A "; break;
	}

}

void traverse_rom(std::vector<uint8_t>& hex_data)
{
	// FIXME: only for debug. normally, i should start from 0.
	//int i = 0;
	int i = 2;
	while (i < hex_data.size())
	{
		disassember(hex_data, i);
		i += 2;
		//if (i > 10)
			break;
	}
}

