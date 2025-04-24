#pragma once
#include "../Headers/Head_2.h"

vector<uint8_t> decodeORA(const vector<string>& operands) {
    if (operands.size() != 1) {
        throw invalid_argument("ORA instruction requires exactly one operand.");
    }

    const string& reg = operands[0];
    if (reg == "B") return { 0xB0 };
    if (reg == "C") return { 0xB1 };
    if (reg == "D") return { 0xB2 };
    if (reg == "E") return { 0xB3 };
    if (reg == "H") return { 0xB4 };
    if (reg == "L") return { 0xB5 };
    if (reg == "M") return { 0xB6 };
    if (reg == "A") return { 0xB7 };

    throw invalid_argument("Invalid operand for ORA instruction: " + reg);
}
