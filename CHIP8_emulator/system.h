#pragma once
#include <stdint.h>
#include <vector>

std::vector<uint8_t> memory = []() { std::vector<uint8_t> memory; memory.reserve(1024 * 4); return memory; }();
std::vector<uint16_t> registers = []() { std::vector<uint16_t> registers; registers.reserve(16); return registers; }();


