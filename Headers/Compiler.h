#include "Head_1.h"
#include "CPU.h"

class Compiler {
public:
	static unordered_map<string, uint16_t> symbolTable;
	static vector<uint8_t> compile(CPU& cpu, const string& line, uint16_t& addr);
	static void buildSymbolTable(vector<string>& assembled_code, uint16_t& addr);
};