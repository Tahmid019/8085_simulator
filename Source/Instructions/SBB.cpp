#pragma once
#include "../Headers/Head_2.h"

vector<uint8_t> decodeSBB(const vector<string>& operands) {
    if (operands.size() != 1) {
        throw invalid_argument("SBB instruction requires exactly one operand.");
    }
    const string& reg = operands[0];
    if (reg == "B") return { 0x98 };
    if (reg == "C") return { 0x99 };
    if (reg == "D") return { 0x9A };
    if (reg == "E") return { 0x9B };
    if (reg == "H") return { 0x9C };
    if (reg == "L") return { 0x9D };
    if (reg == "M") return { 0x9E };
    if (reg == "A") return { 0x9F };
    throw invalid_argument("Invalid operand for SBB instruction: " + reg);
}
