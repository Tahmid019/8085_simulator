#include "../Headers/Head_1.h"
#include "../Headers/Decoder.h"
#include "../Headers/Instructions.h"

vector<uint8_t> Decoder::decode(string& mnemonic, vector<string>& operands) {
    string upper = mnemonic;
    transform(upper.begin(), upper.end(), upper.begin(), toupper);

	if (instructionSet.find(upper) == instructionSet.end()) {
		throw runtime_error("Unknown instruction: " + mnemonic);
		return {};
	}

	Instruction it = instructionSet[upper];
	return it.decoder(operands);
}