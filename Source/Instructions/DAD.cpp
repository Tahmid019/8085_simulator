#pragma once
#include "../Headers/Head_2.h"

vector<uint8_t> decodeDAD(const vector<string>& operands) {
    if (operands.size() != 1) {
        throw invalid_argument("DAD instruction requires exactly one operand.");
    }

    string rp = operands[0];
    if (rp == "B") return { 0x09 };     
    if (rp == "D") return { 0x19 };     
    if (rp == "H") return { 0x29 };    
    if (rp == "SP") return { 0x39 };    

    throw invalid_argument("Invalid register pair for DAD instruction: " + rp);
}

