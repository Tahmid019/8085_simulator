#pragma once
#include "../Headers/Head_2.h"

vector<uint8_t> decodeADC(const vector<string>& operands) {
    if (operands.size() != 1)
        throw runtime_error("ADC requires one register operand");

    static map<string, uint8_t> reg_map = {
        {"A", 0x8F}, {"B", 0x88}, {"C", 0x89}, {"D", 0x8A},
        {"E", 0x8B}, {"H", 0x8C}, {"L", 0x8D}, {"M", 0x8E}
    };

    string reg = operands[0];
    if (reg_map.find(reg) == reg_map.end())
        throw runtime_error("Invalid register for ADC: " + reg);

    return { reg_map[reg] };
}
