#pragma once
#include "../Headers/Head_2.h"

vector<uint8_t> decodeADD(const vector<string>& operands) {
    if (operands.size() != 1)
        throw runtime_error("ADD requires one register operand");

    static map<string, uint8_t> reg_map = {
        {"A", 0x87}, {"B", 0x80}, {"C", 0x81}, {"D", 0x82},
        {"E", 0x83}, {"H", 0x84}, {"L", 0x85}, {"M", 0x86}
    };

    string reg = operands[0];
    if (reg_map.find(reg) == reg_map.end())
        throw runtime_error("Invalid register for ADD: " + reg);

    return { reg_map[reg] };
}
