#pragma once
#include <cstdint>

struct Registers{
	uint8_t A, B, C, D, E, H, L;
	uint16_t PC, SP;
	uint8_t Flags;
};