#pragma once
#include "../Headers/Head_2.h"

vector<uint8_t> decodeDCR(const vector<string>& operands) {
    if (operands.size() != 1) {
        throw invalid_argument("DCR instruction requires exactly one operand.");
    }

    const string& reg = operands[0];

    if (reg == "B") return { 0x05 };
    if (reg == "C") return { 0x0D };
    if (reg == "D") return { 0x15 };
    if (reg == "E") return { 0x1D };
    if (reg == "H") return { 0x25 };
    if (reg == "L") return { 0x2D };
    if (reg == "M") return { 0x35 };
    if (reg == "A") return { 0x3D };

    throw invalid_argument("Invalid operand for DCR instruction: " + reg);
}

