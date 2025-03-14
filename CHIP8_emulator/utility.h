# pragma once
#include <stdint.h>
#include <vector>

std::vector<uint8_t> read_hex_file(const char*);
void disassember(std::vector<uint8_t>&, int&);
void traverse_rom(std::vector<uint8_t>&);
