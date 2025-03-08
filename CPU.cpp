#include "CPU.h"
#include "utils.h"
#include <iostream>

void CPU::execute(uint8_t opcode) {
    std::cout << "Executing Opcode: " << std::hex << (int)opcode << std::endl;

    switch (opcode) {
    case 0x3E: {
        uint8_t value = memory.read(reg.PC++);
        reg.A = value;
        debug(0x3E, (int)reg.A);
        break;
    }

    case 0x78: {
        reg.A = reg.B;
        std::cout << "MOV A, B executed. A = " << (int)reg.A << std::endl;
        break;
    }

    case 0x3A: {
        uint16_t addr = memory.read(reg.PC++) | (memory.read(reg.PC++) << 8);
        reg.A = memory.read(addr);
        std::cout << "LDA executed. A = " << (int)reg.A << " from [" << addr << "]" << std::endl;
        break;
    }

    case 0xC6: {
        uint8_t value = memory.read(reg.PC++);
        reg.A += value;
        std::cout << "ADI executed. A = " << (int)reg.A << std::endl;
        break;
    }

    case 0x32: {
        uint16_t addr = memory.read(reg.PC++) | (memory.read(reg.PC++) << 8);
        memory.write(addr, reg.A);
        std::cout << "STA executed. A at [" << addr << "]" << std::endl;
        break;
    }

    case 0x76:
        std::cout << "HLT executed." << std::endl;
        return;

    default:
        std::cout << "Unknown Opcode: " << std::hex << (int)opcode << std::endl;
    }
}

