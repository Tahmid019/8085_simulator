#pragma once
#include "../Headers/Head_2.h"

vector<uint8_t> decodeLXI(const vector<string>& operands) {
    if (operands.size() != 2) {
        throw invalid_argument("LXI instruction requires two operands.");
    }
    const string& rp = operands[0];
    int data = stoi(operands[1], nullptr, 0);
    if (rp == "B") return { 0x01, static_cast<uint8_t>(data & 0xFF), static_cast<uint8_t>((data >> 8) & 0xFF) };
    if (rp == "D") return { 0x11, static_cast<uint8_t>(data & 0xFF), static_cast<uint8_t>((data >> 8) & 0xFF) };
    if (rp == "H") return { 0x21, static_cast<uint8_t>(data & 0xFF), static_cast<uint8_t>((data >> 8) & 0xFF) };
    if (rp == "SP") return { 0x31, static_cast<uint8_t>(data & 0xFF), static_cast<uint8_t>((data >> 8) & 0xFF) };
    throw invalid_argument("Invalid register pair for LXI instruction: " + rp);
}
