#pragma once
#include "../Headers/Head_2.h"
#include "../Headers/utils.h"

vector<uint8_t> decodeJNZ(const vector<string>& operands) {
    if (operands.size() != 1) {
        throw invalid_argument("JNZ instruction requires exactly one operand.");
    }
    uint16_t addr = 0x0000 | ston<uint16_t>(operands[0]);
    return { 0xC2, static_cast<uint8_t>(addr & 0xFF), static_cast<uint8_t>((addr >> 8) & 0xFF) };
}
