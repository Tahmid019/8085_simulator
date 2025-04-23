#include "../Headers/Head_1.h"
#include "../Headers/Parser.h"
#include "../Headers/Instructions.h"
#include "../Headers/Memory.h"


vector<uint8_t> Parser::tokenize(CPU& cpu, const string& line, uint16_t& addr) {
	istringstream iss(line);
	string token;

	vector<string> parts;
	while (getline(iss, token, ' ')) {
		if(token.back() == ',')
			token.pop_back();
		if (!token.empty()) 
			parts.push_back(token);
	}

	vector<uint8_t> bytes;
	if (parts.empty()) return bytes;

	string mne = parts[0];
	cout << parts.size() << endl;
	transform(mne.begin(), mne.end(), mne.begin(), ::toupper);
	
	if (instructionSet.find(mne) == instructionSet.end()) {
		cerr << "Error: Invalid opcode '" << mne << "'." << endl;
		return bytes;
	}
	Instruction inst = instructionSet[mne];
	bytes.push_back(inst.wordSize);

	cpu.memory.write(addr++, inst.opcode);

	while (--inst.wordSize) {
		if (parts.size() <= 1) {
			cerr << "Error: Missing operand for instruction '" << mne << "'." << endl;
			return bytes;
		}
		string operand = parts[1];
		if (operand.find("H")) {
			operand.pop_back();
			cpu.memory.write(addr++, hto8b(operand));
		}
		else if (isdigit(operand[0])) {
			cpu.memory.write(addr++, stoi(operand, nullptr, 16));
		}
		else {
			cerr << "Error: Invalid operand '" << operand << "'." << endl;
			return bytes;
		}
		parts.erase(parts.begin());
	}

	return bytes;
}