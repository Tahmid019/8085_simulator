#pragma once
#include "../Headers/Head_2.h"

vector<uint8_t> decodeDCX(const vector<string>& operands) {
    if (operands.size() != 1) {
        throw invalid_argument("DCX instruction requires exactly one operand.");
    }

    const string& rp = operands[0];

    if (rp == "B") return { 0x0B };
    if (rp == "D") return { 0x1B };
    if (rp == "H") return { 0x2B };
    if (rp == "SP") return { 0x3B };

    throw invalid_argument("Invalid register pair for DCX instruction: " + rp);
}
