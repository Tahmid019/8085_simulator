#pragma once
#include "../Headers/Head_2.h"

vector<uint8_t> decodeANA(const vector<string>& operands) {
    if (operands.size() != 1)
        throw runtime_error("ANA requires one register operand");

    static map<string, uint8_t> reg_map = {
        {"A", 0xA7}, {"B", 0xA0}, {"C", 0xA1}, {"D", 0xA2},
        {"E", 0xA3}, {"H", 0xA4}, {"L", 0xA5}, {"M", 0xA6}
    };

    string reg = operands[0];
    if (reg_map.find(reg) == reg_map.end())
        throw runtime_error("Invalid register for ANA: " + reg);

    return { reg_map[reg] };
}
