#include "IOHandler.h"
#include "Instructions.h"
#include "utils.h"
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
    int ws = 0;

    while (getline(file, strInst)) {
        if (ws>0) {
            std::cerr << ws << std::endl;
            cpu.memory.write(addr++, stoi(strInst));
            message("Loaded at: ", addr - 1);
            ws--;
            continue;
        }
        if (instructionSet.find(strInst) == instructionSet.end()) {
            //std::cerr << ws << std::endl;
            std::cerr << "Error: { " << strInst << " } | Invalid Instruction ..." << std::endl;
            exit(1);
        }

        Instruction Inst = instructionSet[strInst];
        uint8_t oc = Inst.opcode;
        ws = Inst.wordSize;

        switch (ws) {
            case 1: {
                cpu.memory.write(addr++, oc);
                ws--;
                std::cout << "Loaded: " << std::hex << (int)oc << " at " << addr - 1 << std::endl;
                break;
            }
        
            case 2: {
                cpu.memory.write(addr++, oc);
                ws--;
                message("Loaded at: ", addr-1);
                break;
            }
            default: {
                debug("Invalid IO case", 0);
                exit(1);
            }
        }
    }

    file.close();
}


