#include "../Headers/Head_1.h"
#include "../Headers/IOHandler.h"
#include "../Headers/Instructions.h"
#include "../Headers/utils.h"
#include "../Headers/Compiler.h"

void IOHandler::loadProgram(CPU& cpu, vector<string>& assembled_code, uint16_t& init_addr) {
    cerr << " Loading Program > ";

    /*if (assembled_code.empty()) {
        cerr << "Error: No Code Found ... " << endl;
		throw runtime_error("No code found to load.");
    }*/

    Compiler::symbolTable.clear();

    Compiler::buildSymbolTable(assembled_code, init_addr);

    uint16_t addr = init_addr;

    for (auto& line : assembled_code) {
        try {
            size_t commentPos = line.find(';');
            if (commentPos != string::npos) {
                line = line.substr(0, commentPos);
            }

            trim(line);

            if (line.empty()) continue;

            if (line.back() == ':' && line.find(' ') == string::npos) continue;

            Compiler::compile(cpu, line, addr);
        }
        catch (const exception& e) {
            cerr << "Error in line: " << line << endl;
            cerr << e.what() << endl;
			throw runtime_error("Compilation error in line: " + line);
        }
    }

    cerr << " Loaded < " << endl;
    init_addr = addr;
}


