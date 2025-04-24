#pragma once
#include "../Headers/Head_2.h"

vector<uint8_t> decodeSTAXD(const vector<string>& operands) {
    if (!operands.empty()) {
        throw invalid_argument("STAXD instruction takes no operands.");
    }
return { 0x12 };
}
