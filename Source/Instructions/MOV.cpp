#pragma once
#include "../Headers/Head_2.h"

vector<uint8_t> decodeMOV(const vector<string>& operands) {
    static map<string, int> reg = {
    {"B", 0}, {"C", 1}, {"D", 2}, {"E", 3},
    {"H", 4}, {"L", 5}, {"M", 6}, {"A", 7}
    };

    if (operands.size() != 2 || reg.find(operands[0]) == reg.end() || reg.find(operands[1]) == reg.end()) {
        throw runtime_error("Invalid operands for MOV");
    }

    return {static_cast<uint8_t>(0x40 | (reg[operands[0]] << 3) | reg[operands[1]])};
}
