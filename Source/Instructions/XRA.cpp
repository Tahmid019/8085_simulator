#pragma once
#include "../Headers/Head_2.h"

vector<uint8_t> decodeXRA(const vector<string>& operands) {
    if (operands.size() != 1) {
        throw invalid_argument("XRA instruction requires exactly one operand.");
    }
    const string& reg = operands[0];
    if (reg == "B") return { 0xA8 };
    if (reg == "C") return { 0xA9 };
    if (reg == "D") return { 0xAA };
    if (reg == "E") return { 0xAB };
    if (reg == "H") return { 0xAC };
    if (reg == "L") return { 0xAD };
    if (reg == "M") return { 0xAE };
    if (reg == "A") return { 0xAF };
    throw invalid_argument("Invalid operand for XRA instruction: " + reg);
}
