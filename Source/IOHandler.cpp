#include "../Headers/Head_1.h"
#include "../Headers/IOHandler.h"
#include "../Headers/Instructions.h"
#include "../Headers/utils.h"
#include "../Headers/Parser.h"

void IOHandler::initializeData2Memory(CPU& cpu, const string& mem_file) {
    //cpu.memory.loadMemory(mem_file);
    cout << "[ Insert data in Memory ] / [ Press 'R' to Run Anyway ] :\n";
    while (true) {
        string a, b;
        cin >> a;
        if (a == "R" || a == "r") break;
        cin >> b;
        int address = stoi(a, 0, 16);
        int val = stoi(b);
        cpu.memory.write(address, val);
    }
}

void IOHandler::loadProgram(CPU& cpu, string filename, uint16_t& init_addr) {
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "Error: Cant Open the File ... " << filename << std::endl;
        exit(1);
        return;
    }

    uint16_t addr = init_addr;
    std::string strInst;
    int ws = 0;

    while (getline(file, strInst)) {
        removeTrailingSpaces(strInst);
        
		Parser::tokenize(cpu, strInst, addr);
    }

    file.close();
}


