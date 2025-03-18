#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include "utility.h"
#include "system.h"

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
	uint8_t secondnib = (hex_value << 4);
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
		// registers[secondnib] = hex_data[pc+1];
		break;
	}
	case 0x07: 
	{
		//7XNN:	Add the value NN to register VX
		// Pseudo:
		// registers[secondnib] += hex_data[pc+1]; 
		break;
	}
	case 0x08: 
	{
		uint8_t next_firstnib = hex_data[pc + 1] >> 4;
		uint8_t next_secondnib = hex_data[pc + 1] << 4;
		switch (next_secondnib)
		{
		case 0x00:
		{
			// 8XY0: Store the value of register VY in register VX
			// registers[secondnib] = registers[next_firstnib];
			std::cout << std::format("\n8{:#03x}{:#03x}0", secondnib, next_firstnib);
			break;
		}
		case 0x01:
		{
			// 8XY1: Set VX to VX OR VY
			// registers[secondnib] = registers[secondnib] | registers[next_firstnib];
			std::cout << std::format("\n8{:#03x}{:#03x}1", secondnib, next_firstnib);
			break;
		}
		case 0x02:
		{
			// 8XY2: Set VX to VX AND VY
			// registers[secondnib] = registers[secondnib] & registers[next_firstnib];
			std::cout << std::format("\n8{:#03x}{:#03x}2", secondnib, next_firstnib);
			break;
		}
		case 0x03:
		{
			// 8XY3: Set VX to VX XOR VY
			// registers[secondnib] = registers[secondnib] ^ registers[next_firstnib];
			std::cout << std::format("\n8{:#03x}{:#03x}3", secondnib, next_firstnib);
			break;
		}
		case 0x04:
		{
			// 8XY4	Add the value of register VY to register VX; Set VF to 01 if a carry occurs; Set VF to 00 if a carry does not occur
			// int sum = registers[secondnib] + registers[next_firstnib];
			// if (!(sum < registers[secondnib] | sum < registers[next_firstnib])) registers[0x0f] = 0x01;
			std::cout << std::format("\n8{:#03x}{:#03x}4", secondnib, next_firstnib);
			break;
		}
		case 0x05:
		{
			// 8XY5	Subtract the value of register VY from register VX; Set VF to 00 if a borrow occurs; Set VF to 01 if a borrow does not occur
			// int sum = registers[secondnib] - registers[next_firstnib];
			// if (!(sum > registers[secondnib] | sum > registers[next_firstnib])) registers[0x0f] = 0x01;
			std::cout << std::format("\n8{:#03x}{:#03x}5", secondnib, next_firstnib);
			break;
		}
		case 0x06:
		{
			// 8XY6	Store the value of register VY shifted right one bit in register VX; Set register VF to the least significant bit prior to the shift; VY is unchanged
			// registers[0x0f] = registers[next_firstnib] % 2; // the LSB is 1 only when the number is even; otherwise it is odd. If its not portable, then:
			// registers[0x0f] = registers[next_firstnib] & 1; // prefer this one because it is portable
			// registers[secondnib] = (registers[next_firstnib] >> 1);
			std::cout << std::format("\n8{:#03x}{:#03x}6", secondnib, next_firstnib);
			break;
		}
		case 0x07:
		{
			// 8XY7: Set register VX to the value of VY minus VX; Set VF to 00 if a borrow occurs; Set VF to 01 if a borrow does not occur
			// int sum =  registers[next_firstnib] - registers[secondnib];
			// if (!(sum > registers[secondnib] | sum > registers[next_firstnib])) registers[0x0f] = 0x01;
			std::cout << std::format("\n8{:#03x}{:#03x}7", secondnib, next_firstnib);
			break;
		} 
		case 0x0e:
		{
			// 8XYE: Store the value of register VY shifted left one bit in register VX; Set register VF to the most significant bit prior to the shift; VY is unchanged
			// registers[0x0f] = registers[next_firstnib] & 0x80; // since 0x80 in binary is 10000000;
			// registers[secondnib] = (registers[next_firstnib] << 1);
			std::cout << std::format("\n8{:#03x}{:#03x}6", secondnib, next_firstnib);
			break;
		}
		}
		break;
	}
	case 0x09: 
	{
		// 9XY0: Skip the following instruction if the value of register VX is not equal to the value of register VY
		uint8_t register_x{};  // get the values of the resgister using the second nibble
		uint8_t register_y{};
		if (register_x != register_y)
			pc += 2;
		break;
	}
	case 0x0a: 
	{
		// ANNN: Store memory address NNN in register I
		// I is a special register, that is 2 bytes long (unlike the rest which are 1 byte long). It is used for memory (read & write) operations
		uint16_t register_i = ((hex_value << 4) << 8) | (hex_data[pc + 1] << 4);
		// TODO: assign this value to the actual register I
		break;
	}
	case 0x0b: 
	{
		// BNNN: Jump to address NNN + V0
		uint16_t nnn = ((hex_value << 4) << 8) | (hex_data[pc + 1] << 4);
		// Pseudo:
		// pc = nnn + resgisters[0]
		break;
	}
	case 0x0c: 
	{
		// FIXME: the typical range of the generated number is between 0 and 255. enforce it.
		// CXNN: Set VX to a random number with a mask of NN
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<short> distrib(0, 255);
		uint8_t register_x = static_cast<uint8_t>(distrib(gen)) & hex_data[pc+1];
		// registers[secondnib] = register_x;
		break;
	}
	case 0x0d: 
	{
		// this one is a drawing command
		break;
	}
	case 0x0e: 
	{
		switch (hex_data[pc + 1])
		{
		case 0x9e:
		{
			// Pseudo:
			// if (key() == registers[secondnib]) pc += 2;
			break;
		}
		case 0xa1:
		{
			// Pseudo:
			// if (key() != registers[secondnib]) pc += 2;
			break;
		}
		}
		break;
	}
	case 0x0f: 
	{
		switch (hex_data[pc + 1])
		{
		case 0x07:
		{
			// FX07: Store the current value of the delay timer in register VX
			// registers[secondnib] = Clocks.delay_timer;
			break;
		}
		case 0x0a:
		{
			// FX0A: Wait for a keypress and store the result in register VX
			// registersp[secondnib] = get_key();
			break;
		}
		case 0x15:
		{
			// FX15: Set the delay timer to the value of register VX
			// Clocks.delay_timer = registers[secondnib]; 
			break;
		}
		case 0x18:
		{
			// FX18: Set the sound timer to the value of register VX
			// Clocks.sound_timer = registers[secondnib]; 
			break;
		}
		case 0x1e:
		{
			// FX1E: Add the value stored in register VX to register I
			// register_i += registers[secondnib];
			break;
		}
		case 0x29:
		{
			// FX29: Set I to the memory address of the sprite data corresponding to the hexadecimal digit stored in register VX
			break;
		}
		case 0x33:
		{
			// FX33: Store the binary-coded decimal equivalent of the value stored in register VX at addresses I, I + 1, and I + 2
			break;
		}
		case 0x55:
		{
			// FX55: Store the values of registers V0 to VX inclusive in memory starting at address I; I is set to I + X + 1 after operation²
			break;
		}
		case 0x65:
		{
			// FX65	Fill registers V0 to VX inclusive with the values stored in memory starting at address I; I is set to I + X + 1 after operation²
			break;
		}
		}
		break;
	}
	}
}

void traverse_rom(std::vector<uint8_t>& hex_data)
{
	int i = 0;
	while (i < hex_data.size())
	{
		disassember(hex_data, i);
		i += 2;
		if (i > 20)
			break;
	}
}

