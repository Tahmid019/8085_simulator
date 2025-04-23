#pragma once
#include "../Headers/head_1.h"
#include "../Headers/Head_2.h"

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

    uint8_t byte;
    if (data.back() == 'H') {
        data.pop_back();
        byte = static_cast<uint8_t>(stoi(data, nullptr, 16));
    }
    else {
        byte = static_cast<uint8_t>(stoi(data, nullptr, 16));
    }

    return { opcode, byte };
}
