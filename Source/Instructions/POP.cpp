#pragma once
#include "../Headers/Head_2.h"

vector<uint8_t> decodePOP(const vector<string>& operands) {
    if (operands.size() != 1) {
        throw invalid_argument("POP instruction requires exactly one operand.");
    }

    const string& rp = operands[0];
    if (rp == "B") return { 0xC1 };
    if (rp == "D") return { 0xD1 };
    if (rp == "H") return { 0xE1 };
    if (rp == "PSW") return { 0xF1 };

    throw invalid_argument("Invalid register pair for POP instruction: " + rp);
}