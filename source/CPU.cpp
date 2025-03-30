#include "index.h"

int CPU::execute(uint8_t opcode) {
    std::cout << "Executing Opcode: " << std::hex << static_cast<int>(opcode) << std::endl;

    switch (opcode) {

    // === ADC ===

    case 0xCE: { 
        uint8_t value = memory.read(++reg.PC); 
        reg.A = ALU::adc(reg, value); 
        reg.PC++;
        std::cout << "ACI executed. A = " <<   std::hex << static_cast<int>(reg.A) << std::endl;
        break;
    }

    case 0x8F: { 
        reg.A = ALU::adc(reg, reg.A);
        reg.PC++;
        std::cout << "ADC A executed. A = " << std::hex << static_cast<int>(reg.A) << std::endl;
        break;
    }

    case 0x88: { 
        reg.A = ALU::adc(reg, reg.B); 
        reg.PC++;
        std::cout << "ADC B executed. A = " << std::hex << static_cast<int>(reg.A) << std::endl;
        break;
    }

    case 0x89: { 
        reg.A = ALU::adc(reg, reg.C); 
        reg.PC++;
        std::cout << "ADC C executed. A = " << std::hex << static_cast<int>(reg.A) << std::endl;
        break;
    }

    case 0x8A: { 
        reg.A = ALU::adc(reg, reg.D);
        reg.PC++;
        std::cout << "ADC D executed. A = " << std::hex << static_cast<int>(reg.A) << std::endl;
        break;
    }

    case 0x8B: { 
        reg.A = ALU::adc(reg, reg.E);
        reg.PC++;
        std::cout << "ADC E executed. A = " << std::hex << static_cast<int>(reg.A) << std::endl;
        break;
    }

    case 0x8C: { 
        reg.A = ALU::adc(reg, reg.H);
        reg.PC++;
        std::cout << "ADC H executed. A = " << std::hex << static_cast<int>(reg.A) << std::endl;
        break;
    }

    case 0x8D: { 
        reg.A = ALU::adc(reg, reg.L);
        reg.PC++;
        std::cout << "ADC L executed. A = " << std::hex << static_cast<int>(reg.A) << std::endl;
        break;
    }

    case 0x8E: { 
        uint16_t address = (reg.H << 8) | reg.L;
        uint8_t value = memory.read(address);   
        reg.A = ALU::adc(reg, value); 
        reg.PC++;
        std::cout << "ADC M executed. A = " << std::hex << static_cast<int>(reg.A) << std::endl;
        break;
    }

    // === ADD ===

    case 0x87: {
        reg.A = ALU::add(reg, reg.A);
        reg.PC++;
        message("ADD A executed.", reg.A, 0, MessageType::REGISTER);
        break;
    }
    case 0x80: {
        reg.A = ALU::add(reg, reg.B);
        reg.PC++;
        message("ADD B executed.", reg.B, reg.A, MessageType::REGISTER);
        break;
    }
    case 0x81: {
        reg.A = ALU::add(reg, reg.C);
        reg.PC++;
        message("ADD C executed.", reg.C, reg.A, MessageType::REGISTER);
        break;
    }
    case 0x82: {
        reg.A = ALU::add(reg, reg.D);
        reg.PC++;
        message("ADD D executed.", reg.D, reg.A, MessageType::REGISTER);
        break;
    }
    case 0x83: {
        reg.A = ALU::add(reg, reg.E);
        reg.PC++;
        message("ADD E executed.", reg.E, reg.A, MessageType::REGISTER);
        break;
    }
    case 0x84: {
        reg.A = ALU::add(reg, reg.H);
        reg.PC++;
        message("ADD H executed.", reg.H, reg.A, MessageType::REGISTER);
        break;
    }
    case 0x85: {
        reg.A = ALU::add(reg, reg.L);
        reg.PC++;
        message("ADD L executed.", reg.L, reg.A, MessageType::REGISTER);
        break;
    }
    case 0x86: {
        uint16_t address = (reg.H << 8) | reg.L;
        uint8_t value = memory.read(address);
        reg.A = ALU::add(reg, value);
        reg.PC++;
        debug("ADD M executed.", address, value, MessageType::MEMORY);
        message("ADD M executed.", value, reg.A, MessageType::REGISTER);
        break;
    }

    case 0xC6: {
        uint8_t value = memory.read(++reg.PC);
        reg.A = ALU::add(reg, value);
        reg.PC++;
        std::cout << "ADI executed. A = " << std::hex << static_cast<int>(reg.A) << std::endl;
        break;
    }

    // === MVI Instruction Cases ===

    case 0x3E: {
        uint8_t value = memory.read(++reg.PC);
        reg.A = value;
        reg.PC++;
        message("MVI A", reg.A, 0x00, MessageType::REGISTER);
        break;
    }
    case 0x06: {
        uint8_t value = memory.read(++reg.PC);
        reg.B = value;
        reg.PC++;
        message("MVI B", reg.B, 0x00, MessageType::REGISTER);
        break;
    }
    case 0x0E: {
        uint8_t value = memory.read(++reg.PC);
        reg.C = value;
        reg.PC++;
        message("MVI C", reg.C, 0x00, MessageType::REGISTER);
        break;
    }
    case 0x16: {
        uint8_t value = memory.read(++reg.PC);
        reg.D = value;
        reg.PC++;
        message("MVI D", reg.D, 0x00, MessageType::REGISTER);
        break;
    }
    case 0x1E: {
        uint8_t value = memory.read(++reg.PC);
        reg.E = value;
        reg.PC++;
        message("MVI E", reg.E, 0x00, MessageType::REGISTER);
        break;
    }
    case 0x26: {
        uint8_t value = memory.read(++reg.PC);
        reg.H = value;
        reg.PC++;
        message("MVI H", reg.H, 0x00, MessageType::REGISTER);
        break;
    }
    case 0x2E: {
        uint8_t value = memory.read(++reg.PC);
        reg.L = value;
        reg.PC++;
        message("MVI L", reg.L, 0x00, MessageType::REGISTER);
        break;
    }
    case 0x36: {
        uint8_t value = memory.read(++reg.PC);
        uint16_t M_addr = (reg.H) * (pow(2, 4)) + reg.L;
        memory.write(M_addr, value);
        message("MVI M", memory.read(M_addr), 0x00, MessageType::REGISTER);
        break;
    }

    // === MOV Instruction Cases ===
    
    case 0x7F: {  
        reg.A = reg.A;
        message("MOV A, A", reg.A, reg.A, MessageType::REGISTER);
        break;
    }
    case 0x78: {  
        reg.A = reg.B;
        message("MOV A, B", reg.A, reg.B, MessageType::REGISTER);
        break;
    }
    case 0x79: {  
        reg.A = reg.C;
        message("MOV A, C", reg.A, reg.C, MessageType::REGISTER);
        break;
    }
    case 0x7A: {  
        reg.A = reg.D;
        message("MOV A, D", reg.A, reg.D, MessageType::REGISTER);
        break;
    }
    case 0x7B: {  
        reg.A = reg.E;
        message("MOV A, E", reg.A, reg.E, MessageType::REGISTER);
        break;
    }
    case 0x7C: {  
        reg.A = reg.H;
        message("MOV A, H", reg.A, reg.H, MessageType::REGISTER);
        break;
    }
    case 0x7D: {  
        reg.A = reg.L;
        message("MOV A, L", reg.A, reg.L, MessageType::REGISTER);
        break;
    }
    case 0x7E: {  
        uint8_t value = memory.read(reg.H * 16 + reg.L);
        reg.A = value;
        message("MOV A, M", reg.A, value, MessageType::REGISTER);
        break;
    }
    case 0x47: {  
        reg.B = reg.A;
        message("MOV B, A", reg.B, reg.A, MessageType::REGISTER);
        break;
    }
    case 0x40: {  
        reg.B = reg.B;
        message("MOV B, B", reg.B, reg.B, MessageType::REGISTER);
        break;
    }
    case 0x41: {  
        reg.B = reg.C;
        message("MOV B, C", reg.B, reg.C, MessageType::REGISTER);
        break;
    }
    case 0x42: {  
        reg.B = reg.D;
        message("MOV B, D", reg.B, reg.D, MessageType::REGISTER);
        break;
    }
    case 0x43: {  
        reg.B = reg.E;
        message("MOV B, E", reg.B, reg.E, MessageType::REGISTER);
        break;
    }
    case 0x44: {  
        reg.B = reg.H;
        message("MOV B, H", reg.B, reg.H, MessageType::REGISTER);
        break;
    }
    case 0x45: {  
        reg.B = reg.L;
        message("MOV B, L", reg.B, reg.L, MessageType::REGISTER);
        break;
    }
    case 0x46: {  
        uint8_t value = memory.read(reg.H * 16 + reg.L);
        reg.B = value;
        message("MOV B, M", reg.B, value, MessageType::REGISTER);
        break;
    }

    case 0x4F: {  
        reg.C = reg.A;
        message("MOV C, A", reg.C, reg.A, MessageType::REGISTER);
        break;
    }
    case 0x48: {  
        reg.C = reg.B;
        message("MOV C, B", reg.C, reg.B, MessageType::REGISTER);
        break;
    }
    case 0x49: {  
        reg.C = reg.C;
        message("MOV C, C", reg.C, reg.C, MessageType::REGISTER);
        break;
    }
    case 0x4A: {  
        reg.C = reg.D;
        message("MOV C, D", reg.C, reg.D, MessageType::REGISTER);
        break;
    }
    case 0x4B: {  
        reg.C = reg.E;
        message("MOV C, E", reg.C, reg.E, MessageType::REGISTER);
        break;
    }
    case 0x4C: {  
        reg.C = reg.H;
        message("MOV C, H", reg.C, reg.H, MessageType::REGISTER);
        break;
    }
    case 0x4D: {  
        reg.C = reg.L;
        message("MOV C, L", reg.C, reg.L, MessageType::REGISTER);
        break;
    }
    case 0x4E: {  
        uint8_t value = memory.read(reg.H * 16 + reg.L);
        reg.C = value;
        message("MOV C, M", reg.C, value, MessageType::REGISTER);
        break;
    }
    case 0x57: {
        reg.D = reg.A;
        message("MOV D, A", reg.D, reg.A, MessageType::REGISTER);
        break;
    }
    case 0x50: {
        reg.D = reg.B;
        message("MOV D, B", reg.D, reg.B, MessageType::REGISTER);
        break;
    }
    case 0x51: {
        reg.D = reg.C;
        message("MOV D, C", reg.D, reg.C, MessageType::REGISTER);
        break;
    }
    case 0x52: {
        reg.D = reg.D;
        message("MOV D, D", reg.D, reg.D, MessageType::REGISTER);
        break;
    }
    case 0x53: {
        reg.D = reg.E;
        message("MOV D, E", reg.D, reg.E, MessageType::REGISTER);
        break;
    }
    case 0x54: {
        reg.D = reg.H;
        message("MOV D, H", reg.D, reg.H, MessageType::REGISTER);
        break;
    }
    case 0x55: {
        reg.D = reg.L;
        message("MOV D, L", reg.D, reg.L, MessageType::REGISTER);
        break;
    }
    case 0x56: {
        uint8_t value = memory.read(reg.H * 16 + reg.L);
        reg.D = value;
        message("MOV D, M", reg.D, value, MessageType::REGISTER);
        break;
    }
    case 0x5F: {
        reg.E = reg.A;
        message("MOV E, A", reg.E, reg.A, MessageType::REGISTER);
        break;
    }
    case 0x58: {
        reg.E = reg.B;
        message("MOV E, B", reg.E, reg.B, MessageType::REGISTER);
        break;
    }
    case 0x59: {
        reg.E = reg.C;
        message("MOV E, C", reg.E, reg.C, MessageType::REGISTER);
        break;
    }
    case 0x5A: {
        reg.E = reg.D;
        message("MOV E, D", reg.E, reg.D, MessageType::REGISTER);
        break;
    }
    case 0x5B: {
        reg.E = reg.E;
        message("MOV E, E", reg.E, reg.E, MessageType::REGISTER);
        break;
    }
    case 0x5C: {
        reg.E = reg.H;
        message("MOV E, H", reg.E, reg.H, MessageType::REGISTER);
        break;
    }
    case 0x5D: {
        reg.E = reg.L;
        message("MOV E, L", reg.E, reg.L, MessageType::REGISTER);
        break;
    }
    case 0x5E: {
        uint8_t value = memory.read(reg.H * 16 + reg.L);
        reg.E = value;
        message("MOV E, M", reg.E, value, MessageType::REGISTER);
        break;
    }
    case 0x67: {
        reg.H = reg.A;
        message("MOV H, A", reg.H, reg.A, MessageType::REGISTER);
        break;
    }
    case 0x60: {
        reg.H = reg.B;
        message("MOV H, B", reg.H, reg.B, MessageType::REGISTER);
        break;
    }
    case 0x61: {
        reg.H = reg.C;
        message("MOV H, C", reg.H, reg.C, MessageType::REGISTER);
        break;
    }
    case 0x62: {
        reg.H = reg.D;
        message("MOV H, D", reg.H, reg.D, MessageType::REGISTER);
        break;
    }
    case 0x63: {
        reg.H = reg.E;
        message("MOV H, E", reg.H, reg.E, MessageType::REGISTER);
        break;
    }
    case 0x64: {
        reg.H = reg.H;
        message("MOV H, H", reg.H, reg.H, MessageType::REGISTER);
        break;
    }
    case 0x65: {
        reg.H = reg.L;
        message("MOV H, L", reg.H, reg.L, MessageType::REGISTER);
        break;
    }
    case 0x66: {
        uint8_t value = memory.read(reg.H * 16 + reg.L);
        reg.H = value;
        message("MOV H, M", reg.H, value, MessageType::REGISTER);
        break;
    }
    case 0x6F: {
        reg.L = reg.A;
        message("MOV L, A", reg.L, reg.A, MessageType::REGISTER);
        break;
    }
    case 0x68: {
        reg.L = reg.B;
        message("MOV L, B", reg.L, reg.B, MessageType::REGISTER);
        break;
    }
    case 0x69: {
        reg.L = reg.C;
        message("MOV L, C", reg.L, reg.C, MessageType::REGISTER);
        break;
    }
    case 0x6A: {
        reg.L = reg.D;
        message("MOV L, D", reg.L, reg.D, MessageType::REGISTER);
        break;
    }
    case 0x6B: {
        reg.L = reg.E;
        message("MOV L, E", reg.L, reg.E, MessageType::REGISTER);
        break;
    }
    case 0x6C: {
        reg.L = reg.H;
        message("MOV L, H", reg.L, reg.H, MessageType::REGISTER);
        break;
    }
    case 0x6D: {
        reg.L = reg.L;
        message("MOV L, L", reg.L, reg.L, MessageType::REGISTER);
        break;
    }
    case 0x6E: {
        uint8_t value = memory.read(reg.H * 16 + reg.L);
        reg.L = value;
        message("MOV L, M", reg.L, value, MessageType::REGISTER);
        break;
    }
    case 0x77: { 
        memory.write(reg.H * 16 + reg.L, reg.A);
        message("MOV M, A", reg.A, reg.A, MessageType::MEMORY);
        break;
    }
    case 0x70: { 
        memory.write(reg.H * 16 + reg.L, reg.B);
        message("MOV M, B", reg.B, reg.B, MessageType::MEMORY);
        break;
    }
    case 0x71: { 
        memory.write(reg.H * 16 + reg.L, reg.C);
        message("MOV M, C", reg.C, reg.C, MessageType::MEMORY);
        break;
    }
    case 0x72: {  
        memory.write(reg.H * 16 + reg.L, reg.D);
        message("MOV M, D", reg.D, reg.D, MessageType::MEMORY);
        break;
    }
    case 0x73: { 
        memory.write(reg.H * 16 + reg.L, reg.E);
        message("MOV M, E", reg.E, reg.E, MessageType::MEMORY);
        break;
    }
    case 0x74: { 
        memory.write(reg.H * 16 + reg.L, reg.H);
        message("MOV M, H", reg.H, reg.H, MessageType::MEMORY);
        break;
    }
    case 0x75: { 
        memory.write(reg.H * 16 + reg.L, reg.L);
        message("MOV M, L", reg.L, reg.L, MessageType::MEMORY);
        break;
    }

    /*
     === INPUT - OUTPUT ===
    */

    case 0xD3: { 
        uint8_t port_address = memory.read(++reg.PC);
        reg.PC++;
        // implement IO memory
        message("OUT ", port_address, reg.A, MessageType::REGISTER);
        break;
    }

    // === ALU Instruction ===

   /* case 0xCE: {

    }*/

    case 0x3A: {
        uint16_t addr = memory.read(reg.PC++) | (memory.read(reg.PC++) << 8);
        reg.A = memory.read(addr);
        std::cout << "LDA executed. A = " << std::hex << static_cast<int>(reg.A) << " from [" << addr << "]" << std::endl;
        break;
    }

    case 0x32: {
        uint16_t addr = memory.read(reg.PC++) | (memory.read(reg.PC++) << 8);
        memory.write(addr, reg.A);
        std::cout << "STA executed. A at [" << std::hex << static_cast<int>(addr) << "]" << std::endl;
        break;
    }

    case 0x76:
        //debug("HLT", opcode);
        return -1;

    default:
        std::cout << "Unknown Opcode: " << std::hex << static_cast<int>(opcode) << std::endl;
    }



    return 0;
}

