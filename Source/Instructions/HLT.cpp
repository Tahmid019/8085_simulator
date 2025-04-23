#pragma once
#include "../Headers/Head_2.h"

vector<uint8_t> decodeHLT(const vector<string>& operands) {
    return {static_cast<uint8_t>(0x76)};
}
