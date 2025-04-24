#pragma once
#include "../Headers/Head_2.h"

vector<uint8_t> decodeINX(const vector<string>& operands) {
    if (operands.size() != 1) {
        throw invalid_argument("INX instruction requires exactly one operand.");
    }

    const string& rp = operands[0];

    if (rp == "B") return { 0x03 };
    if (rp == "D") return { 0x13 };
    if (rp == "H") return { 0x23 };
    if (rp == "SP") return { 0x33 };

    throw invalid_argument("Invalid register pair for INX instruction: " + rp);
}
