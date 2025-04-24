#pragma once
#include "../Headers/Head_2.h"

vector<uint8_t> decodeLDAX(const vector<string>& operands) {
    if (operands.size() != 1) {
        throw invalid_argument("LDAX instruction requires exactly one operand.");
    }
    const string& rp = operands[0];
    if (rp == "B") return { 0x0A };
    if (rp == "D") return { 0x1A };
    throw invalid_argument("Invalid register pair for LDAX instruction: " + rp);
}
