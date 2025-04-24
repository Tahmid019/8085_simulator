#pragma once
#include "../Headers/Head_2.h"

vector<uint8_t> decodePUSH(const vector<string>& operands) {
    if (operands.size() != 1) {
        throw invalid_argument("PUSH instruction requires exactly one operand.");
    }

    const string& rp = operands[0];
    if (rp == "B") return { 0xC5 };
    if (rp == "D") return { 0xD5 };
    if (rp == "H") return { 0xE5 };
    if (rp == "PSW") return { 0xF5 };

    throw invalid_argument("Invalid register pair for PUSH instruction: " + rp);
}