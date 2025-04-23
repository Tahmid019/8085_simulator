#include "Head_1.h"
#include "CPU.h"

class Parser {
public:
	static vector<uint8_t> tokenize(CPU& cpu, const string& line, uint16_t& addr);
};