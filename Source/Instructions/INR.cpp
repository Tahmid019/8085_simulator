#pragma once
#include "../Headers/Head_2.h"

vector<uint8_t> decodeINR(const vector<string>& operands) {
    if (operands.size() != 1) {
        throw invalid_argument("INR instruction requires exactly one operand.");
    }

    const string& reg = operands[0];

    if (reg == "B") return { 0x04 };
    if (reg == "C") return { 0x0C };
    if (reg == "D") return { 0x14 };
    if (reg == "E") return { 0x1C };
    if (reg == "H") return { 0x24 };
    if (reg == "L") return { 0x2C };
    if (reg == "M") return { 0x34 };
    if (reg == "A") return { 0x3C };

    throw invalid_argument("Invalid operand for INR instruction: " + reg);
}
