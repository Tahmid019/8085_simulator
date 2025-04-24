#pragma once
#include "../Headers/Head_2.h"
#include "../Headers/utils.h"

vector<uint8_t> decodeOUT(const vector<string>& operands) {
    if (operands.size() != 1) {
        throw invalid_argument("OUT instruction requires exactly one operand.");
    }

    uint8_t port;
    try {
        port = 0x00 | ston<uint8_t>(operands[0]);;
    }
    catch (...) {
        throw invalid_argument("Invalid port number for OUT instruction: " + operands[0]);
    }

    if (port < 0x00 || port > 0xFF) {
        throw invalid_argument("Port number out of range for OUT instruction: " + operands[0]);
    }

    return { 0xD3, static_cast<uint8_t>(port) };
}

