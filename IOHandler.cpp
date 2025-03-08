#include "IOHandler.h"
#include "Instructions.h"
#include <iostream>
#include <string>

void IOHandler::loadProgram(const char* filename, CPU& cpu) {
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "Error: Cant Open the File ... " << filename << std::endl;
        return;
    }

    uint16_t addr = 0x0000;
    std::string strInst;

    while (getline(file, strInst)) {
        if (instructionSet.find(strInst) == instructionSet.end()) {
            std::cerr << "Error: { " << strInst << " } | Invalid Instruction ..." << std::endl;
            exit(1);
        }

        Instruction Inst = instructionSet[strInst];
        uint8_t oc = Inst.opcode;

        cpu.memory.write(addr++, oc);
        std::cout << "Loaded: " << std::hex << (int)oc << " at " << addr - 1 << std::endl;
    }

    file.close();
}


