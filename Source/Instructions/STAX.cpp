#pragma once
#include "../Headers/Head_2.h"

vector<uint8_t> decodeSTAX(const vector<string>& operands) {
    if (operands.empty() || operands.size() > 1) {
        throw invalid_argument("STAX instruction takes one operands.");
    }
    if (operands[0] == "B") return {0x02};
	if (operands[0] == "D") return {0x12};
    
	throw invalid_argument("Invalid operand for STAX instruction. Use 'B' or 'D'.");
}
