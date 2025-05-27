#include "../Headers/Head_1.h"
#include "../Headers/Parser.h"
#include "../Headers/Instructions.h"
#include "../Headers/Memory.h"



unordered_map<std::string, uint16_t> Parser::symbolTable;

vector<uint8_t> Parser::tokenize(CPU& cpu, const string& line, uint16_t& addr) {
	istringstream iss(line);
	string token;
	vector<string> parts;
	
	while (getline(iss, token, ' ')) {
		
		if (token.empty() || token.front() == ';') break;
		
		token.erase(remove(token.begin(), token.end(), ','), token.end());
		if (!token.empty()) parts.push_back(token);
	}

	if (parts.empty()) return {};

	string addr_ptr;
	if (parts[0].back() == ':') {
		addr_ptr = parts[0].substr(0, parts[0].size()-1);
		symbolTable[addr_ptr] = addr;
		parts.erase(parts.begin());
		if (parts.empty()) return{};
	}

	string mne = parts[0];
	parts.erase(parts.begin());
	transform(mne.begin(), mne.end(), mne.begin(), ::toupper);


	
	if (instructionSet.find(mne) == instructionSet.end()) {
		throw runtime_error("Unknown instruction: " + mne);
	}

	for (auto& part : parts) {
		if (symbolTable.count(part)) {
			part = to_string(symbolTable[part]);
		}
	}

	Instruction inst = instructionSet[mne];
	vector<uint8_t> bytes = inst.decoder(parts);
	int ws = inst.wordSize;

	cpu.memory.write(addr++, bytes[0]);
	t2t_message("Loaded at: ", addr - 1, bytes[0], Type2Tpe::t16_2_8);

	if (ws != bytes.size())
		throw runtime_error("Invalid instruction size: " + mne + " | Expected: " + to_string(ws) + " | Found: " + to_string(bytes.size()));

	for (int i = 1; i < bytes.size(); ++i) {
		cpu.memory.write(addr++, bytes[i]);
		t2t_message("Loaded at: ", addr - 1, bytes[i], Type2Tpe::t16_2_8);
	}

	return {};
}