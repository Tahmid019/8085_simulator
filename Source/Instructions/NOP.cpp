#pragma once
#include "../Headers/Head_2.h"

vector<uint8_t> decodeNOP(const vector<string>& operands) {
    if (!operands.empty()) {
        throw invalid_argument("NOP instruction takes no operands.");
    }
    return { 0x00 };
}
