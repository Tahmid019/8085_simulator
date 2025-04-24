#pragma once
#include "../Headers/Head_2.h"
#include "../Headers/utils.h"

vector<uint8_t> decodeADI(const vector<string>& operands) {
    if (operands.size() != 1)
        throw runtime_error("ADI requires one immediate operand");

    string data = operands[0];
    uint8_t byte = 0x00 | ston<uint8_t>(data);

    return { 0xC6, byte };
}
