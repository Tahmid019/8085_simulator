#include "CPU.h"
#include "utils.h"
#include <iostream>

int CPU::execute(uint8_t opcode) {
    std::cout << "Executing Opcode: " << std::hex << (int)opcode << std::endl;

    switch (opcode) {
    case 0x3E: {
        uint8_t value = memory.read(++reg.PC);
        reg.A = value;
        reg.PC++;
        debug("3E", (int)reg.A);
        break;
    }

    /*
     === MOV Instruction Cases ===
    */

    case 0x7F: {
        reg.A = reg.A;
        message("MOV A, A executed ", opcode);
        break;
    }

    case 0x78: {
        reg.A = reg.B;
        message("MOV A, B executed ", opcode);
        break;
    }

    case 0x79: {
        reg.A = reg.C;
        message("MOV A, C executed ", opcode);
        break;
    }

    case 0x7A: {
        reg.A = reg.D;
        message("MOV A, D executed ", opcode);
        break;
    }

    case 0x7B: {
        reg.A = reg.E;
        message("MOV A, E executed ", opcode);
        break;
    }

    case 0x7C: {
        reg.A = reg.H;
        message("MOV A, H executed ", opcode);
        break;
    }

    case 0x7D: {
        reg.A = reg.L;
        message("MOV A, L executed ", opcode);
        break;
    }

    // MOV A, M

    case 0x47: {
        reg.B = reg.A;
        message("MOV B, A executed ", opcode);
        break;
    }

    /*
     === INPUT - OUTPUT ===
    */

    case 0xD3: { // OUT B
        message("Register B: ", (int)reg.B);
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
        debug("HLT", opcode);
        return -1;

    default:
        std::cout << "Unknown Opcode: " << std::hex << (int)opcode << std::endl;
    }

    return 0;
}

