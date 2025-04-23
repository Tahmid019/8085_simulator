#include "../Headers/Head_1.h"
#include "../Headers/Decoder.h"
#include "../Headers/Instructions.h"

uint8_t Decoder::decode(string& mnemonic, vector<string>& operands) {
    string upper = mnemonic;
    transform(upper.begin(), upper.end(), upper.begin(), toupper);

	auto it = instructionSet.find(upper);
	if (it != instructionSet.end()) {
		return it->(operands);
	}else
		throw runtime_error("Unknown instruction: " + mnemonic);
	return 0x00;
}