#pragma once
#include "../Headers/Head_2.h"
#include "../Headers/utils.h"

vector<uint8_t> decodeACI(const vector<string>& operands) {
    if (operands.size() != 1) throw runtime_error("ACI requires one operand");
    string data = operands[0];
    uint8_t byte = 0x00 | ston<uint8_t>(data);
    return { 0xCE, byte };
}
