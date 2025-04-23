#include "../Headers/Head_1.h"
#include "../Headers/Parser.h"


vector<uint8_t> Parser::tokenize(const string& line) {
	istringstream iss(line);
	string token;

	vector<string> parts;
	while (getline(iss, token, ' ')) {
		if(token.back() == ',')
			token.pop_back();
		if (!token.empty()) 
			parts.push_back(token);
	}

	static const map<string, uint8_t> opcode_map = {
		{"MOV", 0x40}
	};

	vector<uint8_t> bytes;
	if (parts.empty()) return bytes;

	string mne = parts[0];
	transform(mne.begin(), mne.end(), mne.begin(), ::toupper);
	
	auto it = opcode_map.find(mne);
	if (it == opcode_map.end()) {
		cerr << "Error: Invalid opcode '" << mne << "'." << endl;
		return bytes;
	}
	bytes.push_back(it->second);

	if (parts.size() == 1) {
		uint16_t val = static_cast<uint16_t>(stoul(parts[1], nullptr, 0));
		bytes.push_back(static_cast<uint8_t>(val & 0xFF));
	}
	else if (mne == "MOV" && parts.size() == 3) {

	}
}