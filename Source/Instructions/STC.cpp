#pragma once
#include "../Headers/Head_2.h"

vector<uint8_t> decodeSTC(const vector<string>& operands) {
    if (!operands.empty()) {
        throw invalid_argument("STC instruction takes no operands.");
    }
return { 0x37 };
}
