#pragma once
#include "../Headers/Head_2.h"

vector<uint8_t> decodeSUB(const vector<string>& operands) {
    if (operands.size() != 1) {
        throw invalid_argument("SUB instruction requires exactly one operand.");
    }
    const string& reg = operands[0];
    if (reg == "B") return { 0x90 };
    if (reg == "C") return { 0x91 };
    if (reg == "D") return { 0x92 };
    if (reg == "E") return { 0x93 };
    if (reg == "H") return { 0x94 };
    if (reg == "L") return { 0x95 };
    if (reg == "M") return { 0x96 };
    if (reg == "A") return { 0x97 };
    throw invalid_argument("Invalid operand for SUB instruction: " + reg);
}
