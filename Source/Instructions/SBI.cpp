#pragma once
#include "../Headers/Head_2.h"
#include "../Headers/utils.h"

vector<uint8_t> decodeSBI(const vector<string>& operands) {
    if (operands.size() != 1) {
        throw invalid_argument("SBI instruction requires exactly one operand.");
    }
    uint8_t data = 0x00 | ston<uint8_t>(operands[0]);
    return { 0xDE, static_cast<uint8_t>(data & 0xFF) };
}
