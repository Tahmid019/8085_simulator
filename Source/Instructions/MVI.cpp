#pragma once
#include "../Headers/Head_2.h"
#include "../Headers/utils.h"

vector<uint8_t> decodeMVI(const vector<string>& operands) {
    static map<string, uint8_t> mviOpcodes = {
        {"B", 0x06}, {"C", 0x0E}, {"D", 0x16}, {"E", 0x1E},
        {"H", 0x26}, {"L", 0x2E}, {"M", 0x36}, {"A", 0x3E}
    };

    if (operands.size() != 2) {
        throw runtime_error("MVI requires 2 operands");
    }

    string reg = operands[0];
    string data = operands[1];

    if (mviOpcodes.find(reg) == mviOpcodes.end()) {
        throw runtime_error("Invalid register in MVI: " + reg);
    }

    uint8_t opcode = mviOpcodes[reg];

    uint8_t byte = 0x00 | ston<uint8_t>(operands[0]);

    return { opcode, byte };
}
