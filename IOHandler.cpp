#include "IOHandler.h"
#include <iostream>

void IOHandler::loadProgram(const char* filename, CPU& cpu) {
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "Error: Could not open " << filename << std::endl;
        return;
    }

    uint16_t addr = 0x0000;
    uint8_t opcode;

    while (file >> std::hex >> opcode) {
        cpu.memory.write(addr++, opcode);
        std::cout << "Loaded: " << std::hex << (int)opcode << " at " << addr - 1 << std::endl;
    }

    file.close();
}


