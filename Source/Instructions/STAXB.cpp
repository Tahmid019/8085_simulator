#pragma once
#include "../Headers/Head_2.h"

vector<uint8_t> decodeSTAXB(const vector<string>& operands) {
    if (!operands.empty()) {
        throw invalid_argument("STAXB instruction takes no operands.");
    }
return { 0x02 };
}
