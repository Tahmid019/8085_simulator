#include "../Headers/Head_1.h"
#include "../Headers/IOHandler.h"
#include "../Headers/Instructions.h"
#include "../Headers/utils.h"
#include "../Headers/Compiler.h"

void IOHandler::initializeData2Memory(CPU& cpu, const string& mem_file) {
    //cpu.memory.loadMemory(mem_file);
    //cout << "[ Insert data in Memory ] / [ Press 'R' to Run Anyway ] :\n";
    //while (true) {
    //    string a, b;
    //    cin >> a;
    //    if (a == "R" || a == "r") break;
    //    cin >> b;
    //    int address = stoi(a, 0, 16);
    //    int val = stoi(b);
    //    cpu.memory.write(address, val);
    //}
}

void IOHandler::loadProgramFile(CPU& cpu, string filename, uint16_t& init_addr) {
    ifstream file(filename);

    if (!file) {
        std::cerr << "Error: Cant Open the File ... " << filename << std::endl;
        exit(1);
        return;
    }
    
	vector<string> assembled_code;
    string strInst;
    while (getline(file, strInst)) {
		assembled_code.push_back(strInst);
    }

    file.close();

	loadProgram(cpu, assembled_code, init_addr);
}

void IOHandler::loadProgram(CPU& cpu, vector<string>& assembled_code, uint16_t& init_addr) {
    if (assembled_code.empty()) {
        cerr << "Error: No Code Found ... " << endl;
		throw runtime_error("No code found to load.");
    }

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

    init_addr = addr;
}


