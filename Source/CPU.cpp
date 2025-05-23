#include "../Headers/Head_1.h"
#include "../Headers/CPU.h"
#include "../Headers/utils.h"

int CPU::execute(uint8_t opcode) {
    std::cout << "Executing Opcode: " << std::hex << static_cast<int>(opcode) << std::endl;

    switch (opcode) {

    // === ACI ===

    case 0xCE: { 
        uint8_t value = memory.read(++reg.PC); 
        reg.A = ALU::adc(reg, value); 
        reg.PC++;
        std::cout << "ACI executed. A = " <<   std::hex << static_cast<int>(reg.A) << std::endl;
        break;
    }

    // === ADC ===

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
        message("ADD B executed.", reg.A, reg.B,  MessageType::REGISTER);
        break;
    }
    case 0x81: {
        reg.A = ALU::add(reg, reg.C);
        reg.PC++;
        message("ADD C executed.", reg.A, reg.C, MessageType::REGISTER);
        break;
    }
    case 0x82: {
        reg.A = ALU::add(reg, reg.D);
        reg.PC++;
        message("ADD D executed.", reg.A, reg.D, MessageType::REGISTER);
        break;
    }
    case 0x83: {
        reg.A = ALU::add(reg, reg.E);
        reg.PC++;
        message("ADD E executed.", reg.A, reg.E, MessageType::REGISTER);
        break;
    }
    case 0x84: {
        reg.A = ALU::add(reg, reg.H);
        reg.PC++;
        message("ADD H executed.", reg.A, reg.H, MessageType::REGISTER);
        break;
    }
    case 0x85: {
        reg.A = ALU::add(reg, reg.L);
        reg.PC++;
        message("ADD L executed.", reg.A, reg.L, MessageType::REGISTER);
        break;
    }
    case 0x86: {
        uint16_t address = reg.HL.get();
        uint8_t value = memory.read(address);
        reg.A = ALU::add(reg, value);
        reg.PC++;
        debug("ADD M executed.", address, value, MessageType::MEMORY);
        message("ADD M executed.", reg.A, value, MessageType::REGISTER);
        break;
    }

    // === ADI ===

    case 0xC6: {
        uint8_t value = memory.read(++reg.PC);
        reg.A = ALU::add(reg, value);
        reg.PC++;
        std::cout << "ADI executed. A = " << std::hex << static_cast<int>(reg.A) << std::endl;
        break;
    }

    // === ANA ===

    case 0xA7: {
        reg.A = ALU::ana(reg, reg.A);
        reg.PC++;
        message("ANA A executed.", reg.A, 0, MessageType::REGISTER);
        break;
    }
    case 0xA0: {
        reg.A = ALU::ana(reg, reg.B);
        reg.PC++;
        message("ANA B executed.  => [B] - [A] : ", reg.B, reg.A, MessageType::REGISTER);
        break;
    }
    case 0xA1: {
        reg.A = ALU::ana(reg, reg.C);
        reg.PC++;
        message("ANA C executed.  => [C] - [A] : ", reg.C, reg.A, MessageType::REGISTER);
        break;
    }
    case 0xA2: {
        reg.A = ALU::ana(reg, reg.D);
        reg.PC++;
        message("ANA D executed.  => [D] - [A] : ", reg.D, reg.A, MessageType::REGISTER);
        break;
    }
    case 0xA3: {
        reg.A = ALU::ana(reg, reg.E);
        reg.PC++;
        message("ANA E executed.  => [E] - [A] : ", reg.E, reg.A, MessageType::REGISTER);
        break;
    }
    case 0xA4: {
        reg.A = ALU::ana(reg, reg.H);
        reg.PC++;
        message("ANA H executed.  => [H] - [A] : ", reg.H, reg.A, MessageType::REGISTER);
        break;
    }
    case 0xA5: {
        reg.A = ALU::ana(reg, reg.L);
        reg.PC++;
        message("ANA L executed.  => [L] - [A] : ", reg.L, reg.A, MessageType::REGISTER);
        break;
    }
    case 0xA6: {
        uint16_t address = (reg.H << 8) | reg.L;
        uint8_t value = memory.read(address);
        debug("ANA M executed.", address, value, MessageType::MEMORY);
        reg.A = ALU::ana(reg, value);
        reg.PC++;
        message("ANA M executed.  => [M] - [A] : ", value, reg.A, MessageType::REGISTER);
        break;
    }

    // === ANI ===

    case 0xE6: {
        uint8_t value = memory.read(++reg.PC);
        reg.PC++;
        message("original [A]: ", reg.A, 0, MessageType::REGISTER);
        reg.A = ALU::ana(reg, value);
        message("ANI executed.  => [A] - val : ", reg.A, value, MessageType::REGISTER);
        break;
    }

    // === CALL etc ... ===

    case 0xCD: {
        uint16_t address = memory.read(++reg.PC) | (memory.read(++reg.PC) << 8); // little Endian
        reg.PC++;
        memory.write(--reg.SP, (reg.PC >> 8) & 0xFF); // higher 
        memory.write(--reg.SP, reg.PC & 0xFF); // lower  
        reg.PC = address;
        t2t_message("[MEMORY] CALL executed.\n(low) [SP] - [[SP]]", reg.SP.get(), memory.read(reg.SP.get()), Type2Tpe::t16_2_8);
        t2t_message("(high) [SP] - [[SP]]", reg.SP.get()+1, memory.read(reg.SP.get()+1), Type2Tpe::t16_2_8);
        break;
    }
    case 0xDC: { // CALL if carry 1
        if ((reg.Flags & 0x01) == 0x01) { 
            uint16_t address = memory.read(++reg.PC) | (memory.read(++reg.PC) << 8);
            reg.PC++;
            memory.write(reg.SP--, reg.PC & 0xFF);
            memory.write(reg.SP--, (reg.PC >> 8) & 0xFF);
            reg.PC = address;
            debug("CC executed. --> ", address, 0, MessageType::MEMORY);
        }
        else {
            reg.PC += 3; 
            message("CC skipped as Carry flag is not set.",0,0,MessageType::INFO);
        }
        break;
    }
    case 0xFC: {
        if ((reg.Flags & 0x80) == 0x80) { // CALL if Sign 1
            uint16_t address = memory.read(++reg.PC) | (memory.read(++reg.PC) << 8);
            reg.PC++;
            memory.write(reg.SP--, reg.PC & 0xFF);
            memory.write(reg.SP--, (reg.PC >> 8) & 0xFF);
            reg.PC = address;
            debug("CM executed. --> ", address, 0, MessageType::MEMORY);
        }
        else {
            reg.PC += 3;
            message("CM skipped as Sign flag is not set.", 0, 0, MessageType::INFO);
        }
        break;
    }
    case 0x2F: {
        reg.A = ~reg.A; 
        reg.PC++;
        message("CMA executed.  => [A] : ", reg.A, 0, MessageType::REGISTER);
        break;
    }
    case 0x3F: {
        reg.Flags ^= 0x01;
        reg.PC++;
        message("CMC executed.", 0, 0, MessageType::REGISTER);
        break;
    }

    // === CMP ===

    case 0xBF: {
        ALU::cmp(reg, reg.A);
        reg.PC++;
        message("CMP A executed.", reg.A, 0, MessageType::REGISTER);
        break;
    }
    case 0xB8: {
        ALU::cmp(reg, reg.B);
        reg.PC++;
        message("CMP B executed.", reg.B, 0, MessageType::REGISTER);
        break;
    }
    case 0xB9: {
        ALU::cmp(reg, reg.C);
        reg.PC++;
        message("CMP C executed.", reg.C, 0, MessageType::REGISTER);
        break;
    }
    case 0xBA: {
        ALU::cmp(reg, reg.D);
        reg.PC++;
        message("CMP D executed.", reg.D, 0, MessageType::REGISTER);
        break;
    }
    case 0xBB: {
        ALU::cmp(reg, reg.E);
        reg.PC++;
        message("CMP E executed.", reg.E, 0, MessageType::REGISTER);
        break;
    }
    case 0xBC: {
        ALU::cmp(reg, reg.H);
        reg.PC++;
        message("CMP H executed.", reg.H, 0, MessageType::REGISTER);
        break;
    }
    case 0xBD: {
        ALU::cmp(reg, reg.L);
        reg.PC++;
        message("CMP L executed.", reg.L, 0, MessageType::REGISTER);
        break;
    }
    case 0xBE: {
        uint16_t address = (reg.H << 8) | reg.L;
        uint8_t value = memory.read(address);
        debug("CMP M executed.", address, value, MessageType::MEMORY);
        ALU::cmp(reg, value);
        reg.PC++;
        message("CMP M executed.", value, 0, MessageType::REGISTER);
        break;
    }

    // === CALL if Flag ===

    case 0xD4: { 
        if ((reg.Flags | 0xfe) == 0xfe) {
            reg.PC++;
            uint16_t address = memory.read(reg.PC++) | (memory.read(reg.PC++) << 8);
            memory.write(--reg.SP, reg.PC & 0xFF);
            memory.write(--reg.SP, (reg.PC >> 8) & 0xFF);
            reg.PC = address;
            debug("CNC executed.", address, 0, MessageType::MEMORY);
        }
        else {
            reg.PC += 3;
            message("CNC skipped as Carry flag is set.",0,0,MessageType::INFO);
        }
        break;
    }
    case 0xC4: { // CNZ
        if ((reg.Flags | 0xdf) == 0xdf) {
            reg.PC++;
            uint16_t address = memory.read(reg.PC++) | (memory.read(reg.PC++) << 8);
            memory.write(--reg.SP, reg.PC & 0xFF);
            memory.write(--reg.SP, (reg.PC >> 8) & 0xFF);
            reg.PC = address;
            debug("CNZ executed.", address, 0, MessageType::MEMORY);
        }
        else {
            reg.PC += 3;
            message("CNZ skipped as Zero flag is set.",0, 0, MessageType::INFO);
        }
        break;
    }
    case 0xF4: { // Call if Pos
        if ((reg.Flags | 0x7f) == 0x7f) {
            reg.PC++;
            uint16_t address = memory.read(reg.PC++) | (memory.read(reg.PC++) << 8);
            memory.write(--reg.SP, reg.PC & 0xFF);
            memory.write(--reg.SP, (reg.PC >> 8) & 0xFF);
            reg.PC = address;
            debug("CP executed.", address, 0, MessageType::MEMORY);
        }
        else {
            reg.PC += 3;
            message("CP skipped as Sign flag is set.",0,0, MessageType::INFO);
        }
        break;
    }
    case 0xEC: { 
        if ((reg.Flags | 0xf7) == 0xff) {
            reg.PC++;
            uint16_t address = memory.read(reg.PC++) | (memory.read(reg.PC++) << 8);
            memory.write(--reg.SP, reg.PC & 0xFF);
            memory.write(--reg.SP, (reg.PC >> 8) & 0xFF);
            reg.PC = address;
            debug("CPE executed.", address, 0, MessageType::MEMORY);
        }
        else {
            reg.PC += 3;
            message("CPE skipped as Parity flag is not set.",0,0,MessageType::INFO);
        }
        break;
    }
    case 0xFE: { 
        reg.PC++;
        uint8_t value = memory.read(reg.PC++);
        ALU::cmp(reg, value);
        message("CPI executed.", value,0,MessageType::MEMORY);
        break;
    }
    case 0xE4: {
        if ((reg.Flags | 0xf7) == 0xf7) {
            reg.PC++;
            uint16_t address = memory.read(reg.PC++) | (memory.read(reg.PC++) << 8);
            memory.write(--reg.SP, reg.PC & 0xFF);
            memory.write(--reg.SP, (reg.PC >> 8) & 0xFF);
            reg.PC = address;
            debug("CPO executed.", address, 0, MessageType::MEMORY);
        }
        else {
            reg.PC += 2;
            message("CPO skipped as Parity flag is set.",0,0,MessageType::INFO);
        }
        break;
    }
    case 0xCC: { 
        if ((reg.Flags | 0xdf) == 0xff) {
            reg.PC++;
            uint16_t address = memory.read(reg.PC++) | (memory.read(reg.PC++) << 8);
            memory.write(--reg.SP, reg.PC & 0xFF);
            memory.write(--reg.SP, (reg.PC >> 8) & 0xFF);
            reg.PC = address;
            debug("CZ executed.", address, 0, MessageType::MEMORY);
        }
        else {
            reg.PC += 3;
            message("CZ skipped as Zero flag is not set.",0,0,MessageType::INFO);
        }
        break;
    }

    // === DAA ===

    case 0x27: {
        reg.PC++;
        reg.A = ALU::daa(reg);
        message("DAA executed.", reg.A,0,MessageType::REGISTER);
        break;
    }

    // === DAD === 32-bit - avoid overflow

    case 0x09: { // DAD B
        ALU::dad(reg, reg.BC);
        reg.PC++;
        //message("DAD B executed.", 0, 0, MessageType::INFO);
		t2t_message("DAD B executed. [HL] <- [BC]", reg.HL.get() , reg.BC.get(), Type2Tpe::t16_2_16);
        break;
    }
    case 0x19: { // DAD D
        ALU::dad(reg, reg.DE);
        reg.PC++;
        //message("DAD D executed.", reg.D, reg.H, MessageType::REGISTER);
        t2t_message("DAD D executed. [HL] <- [DE]", reg.HL.get(), reg.DE.get(), Type2Tpe::t16_2_16);
        break;
    }
    case 0x29: { // DAD H
        uint16_t temp = reg.HL.get();
        ALU::dad(reg, reg.HL);
        reg.PC++;
        //message("DAD H executed.", reg.H, reg.H, MessageType::REGISTER);
        t2t_message("DAD H executed. [HL] <- [HL]", reg.HL.get(), temp, Type2Tpe::t16_2_16);
        break;
    }
    case 0x39: { // DAD SP
        uint32_t result = reg.HL.get() + reg.SP; 
        reg.HL.set(static_cast<uint16_t>(result));
		reg.Flags |= (result > 0xFFFF) ? 0x01 : 0x00;
        reg.PC++;
        //message("DAD SP executed.", static_cast<uint8_t>(reg.SP & 0xFF), reg.H, MessageType::REGISTER);
        t2t_message("DAD SP executed.", reg.SP.get(), 0, Type2Tpe::t16_2_16);
        break;
    }

    // === DCR ===

    case 0x3D: { // DCR A
        reg.A--;
		updateFlags<uint8_t>(reg, reg.A, 0xFE);
        reg.PC++;
        message("DCR A executed.", reg.A,0, MessageType::REGISTER);
        break;
    }
    case 0x05: { // DCR B
        reg.B--;
        updateFlags<uint8_t>(reg, reg.B, 0xFE);
        reg.PC++;
        message("DCR B executed.", reg.B,0, MessageType::REGISTER);
        break;
    }
    case 0x0D: { // DCR C
        reg.C--;
        updateFlags<uint8_t>(reg, reg.C, 0xFE);
        reg.PC++;
        message("DCR C executed.", reg.C,0, MessageType::REGISTER);
        break;
    }
    case 0x15: { // DCR D
        reg.D--;
        updateFlags<uint8_t>(reg, reg.D, 0xFE);
        reg.PC++;
        message("DCR D executed.", reg.D,0, MessageType::REGISTER);
        break;
    }
    case 0x1D: { // DCR E
        reg.E--;
		updateFlags<uint8_t>(reg, reg.E, 0xFE);
        reg.PC++;
        message("DCR E executed.", reg.E,0, MessageType::REGISTER);
        break;
    }
    case 0x25: { // DCR H
        reg.H--;
		updateFlags<uint8_t>(reg, reg.H, 0xFE);
        reg.PC++;
        message("DCR H executed.", reg.H,0, MessageType::REGISTER);
        break;
    }
    case 0x2D: { // DCR L
        reg.L--;
		updateFlags<uint8_t>(reg, reg.L, 0xFE);
        reg.PC++;
        message("DCR L executed.", reg.L,0, MessageType::REGISTER);
        break;
    }
    case 0x35: { // DCR M
        uint16_t address = reg.HL.get();
        uint8_t value = memory.read(address) - 1;
        memory.write(address, value);
		updateFlags<uint8_t>(reg, value, 0xFE);
        reg.PC++;
        debug("DCR M executed.", address, value, MessageType::MEMORY);
        message("DCR M executed.", value,0, MessageType::REGISTER);
        break;
    }
    
    // === DCX ===

    case 0x0B: { // DCX B
        reg.BC.set(reg.BC.get() - 1);
		updateFlags<uint16_t>(reg, reg.BC.get(), 0xFE);
        reg.PC++;
        /*message("DCX B executed.", reg.B, reg.C, MessageType::REGISTER);*/
        debug("DCX B: ", reg.BC.get(), memory.read(reg.BC.get()), MessageType::MEMORY);
        break;
    }
    case 0x1B: { // DCX D
        reg.DE.set(reg.DE.get() - 1);
		updateFlags<uint16_t>(reg, reg.DE.get(), 0xFE);
        reg.PC++;
        //message("DCX D executed.", reg.D, reg.E, MessageType::REGISTER);
        debug("DCX D: ", reg.DE.get(), memory.read(reg.DE.get()), MessageType::MEMORY);
        break;
    }
    case 0x2B: { // DCX H
        reg.HL.set(reg.HL.get() - 1);
		updateFlags<uint16_t>(reg, reg.HL.get(), 0xFE);
        reg.PC++;
        //message("DCX H executed.", reg.H, reg.L, MessageType::REGISTER);
        debug("DCX H: ", reg.HL.get(), memory.read(reg.HL.get()), MessageType::MEMORY);
        break;
    }
    case 0x3B: { // DCX SP
        reg.SP--;
		updateFlags<uint16_t>(reg, reg.SP.get(), 0xFE);
        reg.PC++;
        //message("DCX SP executed.", static_cast<uint8_t>(reg.SP & 0xFF),0, MessageType::REGISTER);
		debug("DCX SP: ", static_cast<uint16_t>(reg.SP.get()), memory.read(reg.SP.get()), MessageType::MEMORY);
        break;
    }

    // === Interrupt ===

    case 0xF3: { // DI
        reg.interruptEnabled = false;
        reg.PC++;
        message("DI executed. Interrupts disabled.",0,0, MessageType::INFO);
        break;
    }
    case 0xFB: { // EI
        reg.interruptEnabled = true;
        reg.PC++;
        message("EI executed. Interrupts enabled.",0,0, MessageType::INFO);
        break;
    }

    // === INR ===

    case 0x3C: { // INR A
        reg.A++;
        reg.PC++;
        message("INR A executed.", reg.A, 0, MessageType::REGISTER);
        break;
    }
    case 0x04: { // INR B
        reg.B++;
        reg.PC++;
        message("INR B executed.", reg.B, 0, MessageType::REGISTER);
        break;
    }
    case 0x0C: { // INR C
        reg.C++;
        reg.PC++;
        message("INR C executed.", reg.C, 0, MessageType::REGISTER);
        break;
    }
    case 0x14: { // INR D
        reg.D++;
        reg.PC++;
        message("INR D executed.", reg.D, 0, MessageType::REGISTER);
        break;
    }
    case 0x1C: { // INR E
        reg.E++;
        reg.PC++;
        message("INR E executed.", reg.E, 0, MessageType::REGISTER);
        break;
    }
    case 0x24: { // INR H
        reg.H++;
        reg.PC++;
        message("INR H executed.", reg.H, 0, MessageType::REGISTER);
        break;
    }
    case 0x2C: { // INR L
        reg.L++;
        reg.PC++;
        message("INR L executed.", reg.L, 0, MessageType::REGISTER);
        break;
    }
    case 0x34: { // INR M
        uint16_t address = reg.HL.get();
        uint8_t value = memory.read(address) + 1;
        memory.write(address, value);
        reg.PC++;
        debug("INR M executed.", address, value, MessageType::MEMORY);
        message("INR M executed.", value, 0, MessageType::REGISTER);
        break;
    }

    // === INX ===

    case 0x03: { // INX B
        reg.BC.set(reg.BC.get() + 1);
        reg.PC++;
        //message("INX B executed.", reg.BC.get() & 0xFF, reg.BC.get() >> 8, MessageType::REGISTER);
        debug("INX B: ", reg.BC.get(), memory.read(reg.BC.get()), MessageType::MEMORY);
        break;
    }
    case 0x13: { // INX D
        reg.DE.set(reg.DE.get() + 1);
        reg.PC++;
        //message("INX D executed.", reg.DE.get() & 0xFF, reg.DE.get() >> 8, MessageType::REGISTER);
        debug("INX D: ", reg.DE.get(), memory.read(reg.DE.get()), MessageType::MEMORY);
        break;
    }
    case 0x23: { // INX H
        reg.HL.set(reg.HL.get() + 1);
        reg.PC++;
        //message("INX H executed.", reg.HL.get() & 0xFF, reg.HL.get() >> 8, MessageType::REGISTER);
        debug("INX H: ", reg.HL.get(), memory.read(reg.HL.get()), MessageType::MEMORY);
        break;
    }
    case 0x33: { // INX SP
        reg.SP++;
        reg.PC++;
        //message("INX SP executed.", static_cast<uint8_t>(reg.SP & 0xFF), static_cast<uint8_t>(reg.SP >> 8), MessageType::REGISTER);
        debug("INX SP: ", static_cast<uint16_t>(reg.SP.get()), memory.read(reg.SP.get()), MessageType::MEMORY);
        debug("INX PC: ", static_cast<uint16_t>(reg.PC), 0, MessageType::MEMORY);
        break;
    }

	// === JMP ===

    case 0xDA: { // JC
        uint16_t address = memory.read(++reg.PC) | (memory.read(++reg.PC) << 8);
        reg.PC++;
        if ((reg.Flags & 0x01) == 0x01) {
            reg.PC = address;
            debug("JC executed. Jump taken.", address, 0, MessageType::MEMORY);
        }
        else {
            message("JC executed. Jump not taken.",0,0, MessageType::INFO);
        }
        break;
    }
    case 0xFA: { // JM
        reg.PC++;
        uint16_t address = memory.read(reg.PC++) | (memory.read(reg.PC++) << 8);
        if ((reg.Flags & 0x80) == 0x80) {
            reg.PC = address;
            debug("JM executed. Jump taken.", address, 0, MessageType::MEMORY);
        }
        else {
            message("JM executed. Jump not taken.",0,0, MessageType::INFO);
        }
        break;
    }
    case 0xC3: { // JMP
		reg.PC++;
        reg.PC = memory.read(reg.PC++) | (memory.read(reg.PC++) << 8);
        debug("JMP executed. Unconditional jump.", reg.PC, 0, MessageType::MEMORY);
        break;
    }
    case 0xD2: { // JNC
        reg.PC++;
        uint16_t address = memory.read(reg.PC++) | (memory.read(reg.PC++) << 8);
        if ((reg.Flags & 0x01) == 0x00) {
            reg.PC = address;
            debug("JNC executed. Jump taken.", address, 0, MessageType::MEMORY);
        }
        else {
            message("JNC executed. Jump not taken.",0,0, MessageType::INFO);
        }
        break;
    }
    case 0xC2: { // JNZ
        reg.PC++;
        uint16_t address = memory.read(reg.PC++) | (memory.read(reg.PC++) << 8);
        if ((reg.Flags & 0x20) == 0x00) {
            reg.PC = address;
            debug("JNZ executed. Jump taken.", address, 0, MessageType::MEMORY);
        }
        else {
            message("JNZ executed. Jump not taken.",0,0, MessageType::INFO);
        }
        break;
    }
    case 0xF2: { // JP
        reg.PC++;
        uint16_t address = memory.read(reg.PC++) | (memory.read(reg.PC++) << 8);
        if ((reg.Flags & 0x80) == 0x00) {
            reg.PC = address;
            debug("JP executed. Jump taken.", address, 0, MessageType::MEMORY);
        }
        else {
            message("JP executed. Jump not taken.",0,0, MessageType::INFO);
        }
        break;
    }
    case 0xEA: { // JPE
        reg.PC++;
        uint16_t address = memory.read(reg.PC++) | (memory.read(reg.PC++) << 8);
        if ((reg.Flags & 0x08) == 0x08) {
            reg.PC = address;
            debug("JPE executed. Jump taken.", address, 0, MessageType::MEMORY);
        }
        else {
            message("JPE executed. Jump not taken.",0,0, MessageType::INFO);
        }
        break;
    }
    case 0xE2: { // JPO
        reg.PC++;
        uint16_t address = memory.read(reg.PC++) | (memory.read(reg.PC++) << 8);
        if ((reg.Flags & 0x08) == 0x00) {
            reg.PC = address;
            debug("JPO executed. Jump taken.", address, 0, MessageType::MEMORY);
        }
        else {
            message("JPO executed. Jump not taken.",0,0, MessageType::INFO);
        }
        break;
    }
    case 0xCA: { // JZ
        reg.PC++;
        uint16_t address = memory.read(reg.PC++) | (memory.read(reg.PC++) << 8);
        if ((reg.Flags & 0x20) == 0x20) {
            reg.PC = address;
            debug("JZ executed. Jump taken.", address, 0, MessageType::MEMORY);
        }
        else {
            message("JZ executed. Jump not taken.",0,0, MessageType::INFO);
        }
        break;
    }

    // === LD Type ===

    case 0x3A: { // LDA
        reg.PC++;
        uint16_t address = memory.read(reg.PC++) | (memory.read(reg.PC++) << 8);
        reg.A = memory.read(address);
        message("LDA executed. Loaded value into accumulator.", reg.A, 0, MessageType::REGISTER);
        break;
    }
    case 0x0A: { // LDAX B
        reg.PC++;
        uint16_t address = reg.BC.get();
        reg.A = memory.read(address);
        message("LDAX B executed. Loaded value into accumulator.", reg.A, 0, MessageType::REGISTER);
        break;
    }
    case 0x1A: { // LDAX D
        reg.PC++;
        uint16_t address = reg.DE.get();
        reg.A = memory.read(address);
        message("LDAX D executed. Loaded value into accumulator.", reg.A, 0, MessageType::REGISTER);
        break;
    }
    case 0x2A: { // LHLD
        reg.PC++;
        uint16_t address = memory.read(reg.PC++) | (memory.read(reg.PC++) << 8);
        reg.L = memory.read(address);
        reg.H = memory.read(address + 1);
		reg.HL.set((reg.H << 8) | reg.L);
        message("LHLD executed. Loaded values into H and L registers.", reg.H, reg.L, MessageType::REGISTER);
        break;
    }

    // === LXI ===

    case 0x01: { // LXI B
        reg.PC++;
        reg.C = memory.read(reg.PC++);
        reg.B = memory.read(reg.PC++);
        //reg.BC.set(reg.B << 8 | reg.C);
        //message("LXI B executed. Loaded values into B and C registers.", reg.B, reg.C, MessageType::REGISTER);
        debug("LXI B: ", reg.BC.get(), memory.read(reg.BC.get()), MessageType::MEMORY);
        break;
    }
    case 0x11: { // LXI D
        reg.PC++;
        reg.E = memory.read(reg.PC++);
        reg.D = memory.read(reg.PC++);
        //reg.DE.set(reg.D << 8 | reg.E);
        //message("LXI D executed. Loaded values into D and E registers.", reg.D, reg.E, MessageType::REGISTER);
        debug("LXI D: ", reg.DE.get(), memory.read(reg.DE.get()), MessageType::MEMORY);
        break;
    }
    case 0x21: { // LXI H
        reg.PC++;
        reg.L = memory.read(reg.PC++);
        reg.H = memory.read(reg.PC++);
        //reg.HL.set(reg.H << 8 | reg.L);
        //message("LXI H executed. Loaded values into H and L registers.", reg.H, reg.L, MessageType::REGISTER);
        debug("LXI H: ", reg.HL.get(), memory.read(reg.HL.get()), MessageType::MEMORY);
        break;
    }
    case 0x31: { // LXI SP
        reg.PC++;
        reg.SP.set(memory.read(reg.PC++) | (memory.read(reg.PC++) << 8));
        t2t_message("LXI SP executed. [SP] - [[SP]]: ", (reg.SP.get()), memory.read(reg.SP.get()), Type2Tpe::t16_2_8);
        break;
    }

    // === MVI ===

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
        //reg.BC.set(reg.B << 8 | reg.C);
        reg.PC++;
        message("MVI B", reg.B, 0x00, MessageType::REGISTER);
        break;
    }
    case 0x0E: {
        uint8_t value = memory.read(++reg.PC);
        reg.C = value;
        //reg.BC.set(reg.B << 8 | reg.C);
        reg.PC++;
        message("MVI C", reg.C, 0x00, MessageType::REGISTER);
        break;
    }
    case 0x16: {
        uint8_t value = memory.read(++reg.PC);
        reg.D = value;
        //reg.DE.set(reg.D << 8 | reg)
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
		//reg.HL.set(reg.H << 8 | reg.L);
        reg.PC++;
        message("MVI H", reg.H, 0x00, MessageType::REGISTER);
        break;
    }
    case 0x2E: {
        uint8_t value = memory.read(++reg.PC);
        reg.L = value;
        //reg.HL.set(reg.H << 8 | reg.L);
        reg.PC++;
        message("MVI L", reg.L, 0x00, MessageType::REGISTER);
        break;
    }
    case 0x36: {
        uint8_t value = memory.read(++reg.PC);
        uint16_t M_addr = reg.HL.get();
        //cout << M_addr << endl;
        memory.write(M_addr, value);
        reg.PC++;
        //message("MVI M", memory.read(M_addr), 0x00, MessageType::REGISTER);
        debug("MVI M: ", M_addr, memory.read(M_addr), MessageType::MEMORY);
        break;
    }

    // === MOV Instruction Cases ===
    
    case 0x7F: {  
        reg.A = reg.A;
        reg.PC++;
        message("MOV A, A", reg.A, reg.A, MessageType::REGISTER);
        break;
    }
    case 0x78: {  
        reg.A = reg.B;
        reg.PC++;
        message("MOV A, B", reg.A, reg.B, MessageType::REGISTER);
        break;
    }
    case 0x79: {  
        reg.A = reg.C;
        reg.PC++;
        message("MOV A, C", reg.A, reg.C, MessageType::REGISTER);
        break;
    }
    case 0x7A: {  
        reg.A = reg.D;
        reg.PC++;
        message("MOV A, D", reg.A, reg.D, MessageType::REGISTER);
        break;
    }
    case 0x7B: {  
        reg.A = reg.E;
        reg.PC++;
        message("MOV A, E", reg.A, reg.E, MessageType::REGISTER);
        break;
    }
    case 0x7C: {  
        reg.A = reg.H;
        reg.PC++;
        message("MOV A, H", reg.A, reg.H, MessageType::REGISTER);
        break;
    }
    case 0x7D: {  
        reg.A = reg.L;
        reg.PC++;
        message("MOV A, L", reg.A, reg.L, MessageType::REGISTER);
        break;
    }
    case 0x7E: {  
        uint8_t value = memory.read(reg.HL.get());
        reg.PC++;
        reg.A = value;
        message("MOV A, M", reg.A, value, MessageType::REGISTER);
        break;
    }
    case 0x47: {  
        reg.B = reg.A;
        reg.PC++;
        message("MOV B, A", reg.B, reg.A, MessageType::REGISTER);
        break;
    }
    case 0x40: {  
        reg.B = reg.B;
        reg.PC++;
        message("MOV B, B", reg.B, reg.B, MessageType::REGISTER);
        break;
    }
    case 0x41: {  
        reg.B = reg.C;
        reg.PC++;
        message("MOV B, C", reg.B, reg.C, MessageType::REGISTER);
        break;
    }
    case 0x42: {  
        reg.B = reg.D;
        reg.PC++;
        message("MOV B, D", reg.B, reg.D, MessageType::REGISTER);
        break;
    }
    case 0x43: {  
        reg.B = reg.E;
        reg.PC++;
        message("MOV B, E", reg.B, reg.E, MessageType::REGISTER);
        break;
    }
    case 0x44: {  
        reg.B = reg.H;
        reg.PC++;
        message("MOV B, H", reg.B, reg.H, MessageType::REGISTER);
        break;
    }
    case 0x45: {  
        reg.B = reg.L;
        reg.PC++;
        message("MOV B, L", reg.B, reg.L, MessageType::REGISTER);
        break;
    }
    case 0x46: {  
        uint8_t value = memory.read(reg.HL.get());
        reg.PC++;
        reg.B = value;
        message("MOV B, M", reg.B, value, MessageType::REGISTER);
        break;
    }

    case 0x4F: {  
        reg.C = reg.A;
        reg.PC++;
        message("MOV C, A", reg.C, reg.A, MessageType::REGISTER);
        break;
    }
    case 0x48: {  
        reg.C = reg.B;
        reg.PC++;
        message("MOV C, B", reg.C, reg.B, MessageType::REGISTER);
        break;
    }
    case 0x49: {  
        reg.C = reg.C;
        reg.PC++;
        message("MOV C, C", reg.C, reg.C, MessageType::REGISTER);
        break;
    }
    case 0x4A: {  
        reg.C = reg.D;
        reg.PC++;
        message("MOV C, D", reg.C, reg.D, MessageType::REGISTER);
        break;
    }
    case 0x4B: {  
        reg.C = reg.E;
        reg.PC++;
        message("MOV C, E", reg.C, reg.E, MessageType::REGISTER);
        break;
    }
    case 0x4C: {  
        reg.C = reg.H;
        reg.PC++;
        message("MOV C, H", reg.C, reg.H, MessageType::REGISTER);
        break;
    }
    case 0x4D: {  
        reg.C = reg.L;
        reg.PC++;
        message("MOV C, L", reg.C, reg.L, MessageType::REGISTER);
        break;
    }
    case 0x4E: {  
        uint8_t value = memory.read(reg.HL.get());
        reg.PC++;
        reg.C = value;
        message("MOV C, M", reg.C, value, MessageType::REGISTER);
        break;
    }
    case 0x57: {
        reg.D = reg.A;
        reg.PC++;
        message("MOV D, A", reg.D, reg.A, MessageType::REGISTER);
        break;
    }
    case 0x50: {
        reg.D = reg.B;
        reg.PC++;
        message("MOV D, B", reg.D, reg.B, MessageType::REGISTER);
        break;
    }
    case 0x51: {
        reg.D = reg.C;
        reg.PC++;
        message("MOV D, C", reg.D, reg.C, MessageType::REGISTER);
        break;
    }
    case 0x52: {
        reg.D = reg.D;
        reg.PC++;
        message("MOV D, D", reg.D, reg.D, MessageType::REGISTER);
        break;
    }
    case 0x53: {
        reg.D = reg.E;
        reg.PC++;
        message("MOV D, E", reg.D, reg.E, MessageType::REGISTER);
        break;
    }
    case 0x54: {
        reg.D = reg.H;
        reg.PC++;
        message("MOV D, H", reg.D, reg.H, MessageType::REGISTER);
        break;
    }
    case 0x55: {
        reg.D = reg.L;
        reg.PC++;
        message("MOV D, L", reg.D, reg.L, MessageType::REGISTER);
        break;
    }
    case 0x56: {
        uint8_t value = memory.read(reg.HL.get());
        reg.D = value;
        reg.PC++;
        message("MOV D, M", reg.D, value, MessageType::REGISTER);
        break;
    }
    case 0x5F: {
        reg.E = reg.A;
        reg.PC++;
        message("MOV E, A", reg.E, reg.A, MessageType::REGISTER);
        break;
    }
    case 0x58: {
        reg.E = reg.B;
        reg.PC++;
        message("MOV E, B", reg.E, reg.B, MessageType::REGISTER);
        break;
    }
    case 0x59: {
        reg.E = reg.C;
        reg.PC++;
        message("MOV E, C", reg.E, reg.C, MessageType::REGISTER);
        break;
    }
    case 0x5A: {
        reg.E = reg.D;
        reg.PC++;
        message("MOV E, D", reg.E, reg.D, MessageType::REGISTER);
        break;
    }
    case 0x5B: {
        reg.E = reg.E;
        reg.PC++;
        message("MOV E, E", reg.E, reg.E, MessageType::REGISTER);
        break;
    }
    case 0x5C: {
        reg.E = reg.H;
        reg.PC++;
        message("MOV E, H", reg.E, reg.H, MessageType::REGISTER);
        break;
    }
    case 0x5D: {
        reg.E = reg.L;
        reg.PC++;
        message("MOV E, L", reg.E, reg.L, MessageType::REGISTER);
        break;
    }
    case 0x5E: {
        uint8_t value = memory.read(reg.HL.get());
        reg.E = value;
        reg.PC++;
        message("MOV E, M", reg.E, value, MessageType::REGISTER);
        break;
    }
    case 0x67: {
        reg.H = reg.A;
        //reg.HL.set(reg.H << 8 | reg.L);
        reg.PC++;
        message("MOV H, A", reg.H, reg.A, MessageType::REGISTER);
        break;
    }
    case 0x60: {
        reg.H = reg.B;
        //reg.HL.set(reg.H << 8 | reg.L);
        reg.PC++;
        message("MOV H, B", reg.H, reg.B, MessageType::REGISTER);
        break;
    }
    case 0x61: {
        reg.H = reg.C;
        //reg.HL.set(reg.H << 8 | reg.L);
        reg.PC++;
        message("MOV H, C", reg.H, reg.C, MessageType::REGISTER);
        break;
    }
    case 0x62: {
        reg.H = reg.D;
        //reg.HL.set(reg.H << 8 | reg.L);
        reg.PC++;
        message("MOV H, D", reg.H, reg.D, MessageType::REGISTER);
        break;
    }
    case 0x63: {
        reg.H = reg.E;
        //reg.HL.set(reg.H << 8 | reg.L);
        reg.PC++;
        message("MOV H, E", reg.H, reg.E, MessageType::REGISTER);
        break;
    }
    case 0x64: {
        reg.H = reg.H;
        //reg.HL.set(reg.H << 8 | reg.L);
        reg.PC++;
        message("MOV H, H", reg.H, reg.H, MessageType::REGISTER);
        break;
    }
    case 0x65: {
        reg.H = reg.L;
        //reg.HL.set(reg.H << 8 | reg.L);
        reg.PC++;
        message("MOV H, L", reg.H, reg.L, MessageType::REGISTER);
        break;
    }
    case 0x66: {
        uint8_t value = memory.read(reg.HL.get());
        reg.H = value;
        //reg.HL.set(reg.H << 8 | reg.L);
        reg.PC++;
        message("MOV H, M", reg.H, value, MessageType::REGISTER);
        break;
    }
    case 0x6F: {
        reg.L = reg.A;
        //reg.HL.set(reg.H << 8 | reg.L);
        reg.PC++;
        message("MOV L, A", reg.L, reg.A, MessageType::REGISTER);
        break;
    }
    case 0x68: {
        reg.L = reg.B;
        //reg.HL.set(reg.H << 8 | reg.L);
        reg.PC++;
        message("MOV L, B", reg.L, reg.B, MessageType::REGISTER);
        break;
    }
    case 0x69: {
        reg.L = reg.C;
        //reg.HL.set(reg.H << 8 | reg.L);
        reg.PC++;
        message("MOV L, C", reg.L, reg.C, MessageType::REGISTER);
        break;
    }
    case 0x6A: {
        reg.L = reg.D;
        //reg.HL.set(reg.H << 8 | reg.L);
        reg.PC++;
        message("MOV L, D", reg.L, reg.D, MessageType::REGISTER);
        break;
    }
    case 0x6B: {
        reg.L = reg.E;
        //reg.HL.set(reg.H << 8 | reg.L);
        reg.PC++;
        message("MOV L, E", reg.L, reg.E, MessageType::REGISTER);
        break;
    }
    case 0x6C: {
        reg.L = reg.H;
        //reg.HL.set(reg.H << 8 | reg.L);
        reg.PC++;
        message("MOV L, H", reg.L, reg.H, MessageType::REGISTER);
        break;
    }
    case 0x6D: {
        reg.L = reg.L;
        //reg.HL.set(reg.H << 8 | reg.L);
        reg.PC++;
        message("MOV L, L", reg.L, reg.L, MessageType::REGISTER);
        break;
    }
    case 0x6E: {
        uint8_t value = memory.read(reg.HL.get());
        reg.L = value;
        //reg.HL.set(reg.H << 8 | reg.L);
        reg.PC++;
        message("MOV L, M", reg.L, value, MessageType::REGISTER);
        break;
    }
    case 0x77: { 
        memory.write(reg.HL.get(), reg.A);
        reg.PC++;
        message("MOV M, A", reg.A, reg.A, MessageType::MEMORY);
        break;
    }
    case 0x70: { 
        memory.write(reg.HL.get(), reg.B);
        reg.PC++;
        message("MOV M, B", reg.B, reg.B, MessageType::MEMORY);
        break;
    }
    case 0x71: { 
        memory.write(reg.HL.get(), reg.C);
        reg.PC++;
        message("MOV M, C", reg.C, reg.C, MessageType::MEMORY);
        break;
    }
    case 0x72: {  
        memory.write(reg.HL.get(), reg.D);
        reg.PC++;
        message("MOV M, D", reg.D, reg.D, MessageType::MEMORY);
        break;
    }
    case 0x73: { 
        memory.write(reg.HL.get(), reg.E);
        reg.PC++;
        message("MOV M, E", reg.E, reg.E, MessageType::MEMORY);
        break;
    }
    case 0x74: { 
        memory.write(reg.HL.get(), reg.H);
        reg.PC++;
        message("MOV M, H", reg.H, reg.H, MessageType::MEMORY);
        break;
    }
    case 0x75: { 
        memory.write(reg.HL.get(), reg.L);
        reg.PC++;
        message("MOV M, L", reg.L, reg.L, MessageType::MEMORY);
        break;
    }

    // === NOP ===

    case 0x00: { // NOP
        reg.PC++;
        message("NOP executed. No operation performed.",0,0, MessageType::INFO);
        break;
    }

    // === ORA ===

    case 0xB7: { // ORA A
        ALU::ora(reg, reg.A);
        reg.PC++;
        message("ORA A executed. A |=  itself.", reg.A, 0, MessageType::REGISTER);
        break;
    }
    case 0xB0: { // ORA B
        ALU::ora(reg, reg.B);
        reg.PC++;
        message("ORA B executed. A |=  register B.", reg.A, reg.B, MessageType::REGISTER);
        break;
    }
    case 0xB1: { // ORA C
        ALU::ora(reg, reg.C);
        reg.PC++;
        message("ORA C executed. A |=  register C.", reg.A, reg.C, MessageType::REGISTER);
        break;
    }
    case 0xB2: { // ORA D
        ALU::ora(reg, reg.D);
        reg.PC++;
        message("ORA D executed. A |=  register D.", reg.A, reg.D, MessageType::REGISTER);
        break;
    }
    case 0xB3: { // ORA E
        ALU::ora(reg, reg.E);
        reg.PC++;
        message("ORA E executed. A |=  register E.", reg.A, reg.E, MessageType::REGISTER);
        break;
    }
    case 0xB4: { // ORA H
        ALU::ora(reg, reg.H);
        reg.PC++;
        message("ORA H executed. A |=  register H.", reg.A, reg.H, MessageType::REGISTER);
        break;
    }
    case 0xB5: { // ORA L
        ALU::ora(reg, reg.L);
        reg.PC++;
        message("ORA L executed. A |=  register L.", reg.A, reg.L, MessageType::REGISTER);
        break;
    }
    case 0xB6: { // ORA M
        uint16_t address = reg.HL.get();
        uint8_t value = memory.read(address);
        ALU::ora(reg, value);
        reg.PC++;
        debug("ORA M executed. A |=  memory value.", address, value, MessageType::MEMORY);
        message("ORA M executed.", reg.A, 0, MessageType::REGISTER);
        break;
    }

    // === ORI ===

    case 0xF6: { // ORI
        uint8_t val = memory.read(reg.PC++);
        ALU::ora(reg, val);
        reg.PC++;
        message("ORI executed. A |= val.", reg.A, val, MessageType::REGISTER);
        break;
    }

    // === PCHL ===

    case 0xE9: { // PCHL
        reg.PC = reg.HL.get();
        message("PCHL executed. Program Counter set to HL register pair.", reg.PC & 0xFF, reg.PC >> 8, MessageType::REGISTER);
        break;
    }

    // === POP ===

    case 0xC1: { // POP B
        reg.C = reg.SP.pop(memory);
        reg.B = reg.SP.pop(memory);
        reg.PC++;
        message("POP B executed. Values popped into B and C registers.", reg.B, reg.C, MessageType::REGISTER);
        break;
    }
    case 0xD1: { // POP D
        reg.E = reg.SP.pop(memory);
        reg.D = reg.SP.pop(memory);
        reg.PC++;
        message("POP D executed. Values popped into D and E registers.", reg.D, reg.E, MessageType::REGISTER);
        break;
    }
    case 0xE1: { // POP H
        reg.L = reg.SP.pop(memory);
        reg.H = reg.SP.pop(memory);
        reg.PC++;
        message("POP H executed. Values popped into H and L registers.", reg.H, reg.L, MessageType::REGISTER);
        break;
    }
    case 0xF1: { // POP PSW (Processor Status Word)
        reg.Flags = reg.SP.pop(memory);
        reg.A = reg.SP.pop(memory);
        reg.PC++;
        message("POP PSW executed. Flags and Accumulator updated.", reg.A, reg.Flags, MessageType::REGISTER);
        break;
    }

    // === PUSH ===

    case 0xC5: // PUSH B
        reg.PC++;
        memory.write(--reg.SP, reg.B); // high
        memory.write(--reg.SP, reg.C); // low
        message("PUSH B executed.", 0, 0, MessageType::INFO);
        t2t_message("(high [B]) -> [SP] - [[SP]]: ", (reg.SP.get()+1), memory.read(reg.SP.get()+1), Type2Tpe::t16_2_8);
        t2t_message("(low [C]) -> [SP] - [[SP]]: ", (reg.SP.get()), memory.read(reg.SP.get()), Type2Tpe::t16_2_8);
        break;
    case 0xD5: // PUSH D
        reg.PC++;
        memory.write(--reg.SP, reg.D);
        memory.write(--reg.SP, reg.E); 
        message("PUSH D executed.", 0, 0, MessageType::INFO);
        t2t_message("(high [D]) -> [SP] - [[SP]]: ", (reg.SP.get() + 1), memory.read(reg.SP.get() + 1), Type2Tpe::t16_2_8);
        t2t_message("(low [E]) -> [SP] - [[SP]]: ", (reg.SP.get()), memory.read(reg.SP.get()), Type2Tpe::t16_2_8);
        break;
    case 0xE5: // PUSH H
        reg.PC++;
        memory.write(--reg.SP, reg.H); 
        memory.write(--reg.SP, reg.L); 
        message("PUSH H executed.", 0, 0, MessageType::INFO);
        t2t_message("(high [HJ]) -> [SP] - [[SP]]: ", (reg.SP.get() + 1), memory.read(reg.SP.get() + 1), Type2Tpe::t16_2_8);
        t2t_message("(low [L]) -> [SP] - [[SP]]: ", (reg.SP.get()), memory.read(reg.SP.get()), Type2Tpe::t16_2_8);
        break;
    case 0xF5: // PUSH PSW
        reg.PC++;
        memory.write(--reg.SP, reg.A); 
        memory.write(--reg.SP, reg.Flags);
        message("PUSH PSW executed.", 0, 0, MessageType::INFO);
        t2t_message("(high [A]) -> [SP] - [[SP]]: ", (reg.SP.get() + 1), memory.read(reg.SP.get() + 1), Type2Tpe::t16_2_8);
        t2t_message("(low [Flags]) -> [SP] - [[SP]]: ", (reg.SP.get()), memory.read(reg.SP.get()), Type2Tpe::t16_2_8);
        break;


    // === Rotate & Return ===

    case 0x17: { // RAL
        uint8_t d7 = reg.A & 0x80;
        reg.Flags = (reg.Flags & 0xFE) | ((reg.A & 0x80) != 0);
        reg.A = (reg.A << 1) | ((d7 >> 7) & 0x01);
        reg.PC++;
        message("RAL executed. [A]: ", reg.A,0, MessageType::REGISTER);
        break;
    }
    case 0x1F: { // RAR
        uint8_t d0 = reg.A & 0x01;
        reg.Flags = (reg.Flags & 0xFE) | (reg.A & 0x01);
        reg.A = (reg.A >> 1) | ((d0 << 7) & 0x80);
        reg.PC++;
        message("RAR executed. [A]: ", reg.A, 0, MessageType::REGISTER);
        break;
    }
    case 0x07: { // RLC
        uint8_t carry = reg.Flags & 0x01;
        reg.Flags = (reg.Flags & 0xFE) | ((reg.A & 0x80) != 0);
        reg.A = (reg.A << 1) | (carry & 0x01);
        reg.PC++;
        message("RLC executed. [A]: ", reg.A, 0, MessageType::REGISTER);
        break;
    }
    case 0x0F: { // RRC
        uint8_t carry = reg.Flags & 0x01;
        reg.Flags = (reg.Flags & 0xFE) | (reg.A & 0x01);
        reg.A = (reg.A >> 1) | ((carry << 7) & 0x80);
        reg.PC++;
        message("RRC executed. [A]: ", reg.A, 0, MessageType::REGISTER);
        break;
    }
    case 0xC9: { // RET
        reg.PC = (reg.SP.pop(memory) | (reg.SP.pop(memory) << 8));
        t2t_message("RET executed. [PC]: ", reg.PC, 0, Type2Tpe::t16_2_16);
        break;
    }
    case 0xD8: { // RC
        if (reg.Flags & 0x01) {
            reg.PC = reg.SP.pop(memory) | (reg.SP.pop(memory) << 8);
        }
        else {
            reg.PC++;
        }
        message("RC executed. [PC]: ", reg.PC, 0, MessageType::MEMORY);
        break;
    }
    case 0xC0: { // RNZ
        if (!(reg.Flags & 0x40)) {
            reg.PC = reg.SP.pop(memory) | (reg.SP.pop(memory) << 8);
        }
        else {
            reg.PC++;
        }
        message("RNZ executed. [PC]: ", reg.PC, 0, MessageType::MEMORY);
        break;
    }
    case 0xD0: { // RNC
        if (!(reg.Flags & 0x01)) {
            reg.PC = reg.SP.pop(memory) | (reg.SP.pop(memory) << 8);
        }
        else {
            reg.PC++;
        }
        message("RNC executed. [PC]: ", reg.PC, 0, MessageType::MEMORY);
        break;
    }
    case 0xF0: { // RP - if Positive
        if (!(reg.Flags & 0x80)) {
            reg.PC = reg.SP.pop(memory) | (reg.SP.pop(memory) << 8);
        }
        else {
            reg.PC++;
        }
        message("RP executed. [PC]: ", reg.PC, 0, MessageType::MEMORY);
        break;
    }
    case 0xF8: { // RM - if Minus
        if (reg.Flags & 0x80) {
            reg.PC = reg.SP.pop(memory) | (reg.SP.pop(memory) << 8);
        }
        else {
            reg.PC++;
        }
        message("RM executed. [PC]: ", reg.PC, 0, MessageType::MEMORY);
        break;
    }
    case 0xE8: { // RPE
        if (reg.Flags & 0x04) {
            reg.PC = reg.SP.pop(memory) | (reg.SP.pop(memory) << 8);
        }
        else {
            reg.PC++;
        }
        message("RPE executed. [PC]: ", reg.PC, 0, MessageType::MEMORY);
        break;
    }
    case 0xE0: { // RPO
        if (!(reg.Flags & 0x04)) {
            reg.PC = reg.SP.pop(memory) | (reg.SP.pop(memory) << 8);
        }
        else {
            reg.PC++;
        }
        message("RPO executed. [PC]: ", reg.PC, 0, MessageType::MEMORY);
        break;
    }
    case 0x20: { // RIM
        reg.A = interruptControl.readMask();
        reg.PC++;
        message("RIM executed. [A]: ", reg.A, 0, MessageType::REGISTER);
        break;
    }

    // === RST ===

    case 0xC7: { // RST 0
        reg.SP.push(memory, (reg.PC >> 8) & 0xFF);
        reg.SP.push(memory, reg.PC & 0xFF);
        reg.PC = 0x00;
        break;
    }
    case 0xCF: { // RST 1
        reg.SP.push(memory, (reg.PC >> 8) & 0xFF);
        reg.SP.push(memory, reg.PC & 0xFF);
        reg.PC = 0x08;
        break;
    }
    case 0xD7: { // RST 2
        reg.SP.push(memory, (reg.PC >> 8) & 0xFF);
        reg.SP.push(memory, reg.PC & 0xFF);
        reg.PC = 0x10;
        break;
    }
    case 0xDF: { // RST 3
        reg.SP.push(memory, (reg.PC >> 8) & 0xFF);
        reg.SP.push(memory, reg.PC & 0xFF);
        reg.PC = 0x18;
        break;
    }
    case 0xE7: { // RST 4
        reg.SP.push(memory, (reg.PC >> 8) & 0xFF);
        reg.SP.push(memory, reg.PC & 0xFF);
        reg.PC = 0x20;
        break;
    }
    case 0xEF: { // RST 5
        reg.SP.push(memory, (reg.PC >> 8) & 0xFF);
        reg.SP.push(memory, reg.PC & 0xFF);
        reg.PC = 0x28;
        break;
    }
    case 0xF7: { // RST 6
        reg.SP.push(memory, (reg.PC >> 8) & 0xFF);
        reg.SP.push(memory, reg.PC & 0xFF);
        reg.PC = 0x30;
        break;
    }
    case 0xFF: { // RST 7
        /*reg.SP.push(memory, (reg.PC >> 8) & 0xFF);
        reg.SP.push(memory, reg.PC & 0xFF);
        reg.PC = 0x38;*/
        reg.PC++;
        break;
    }
    case 0xC8: { // RZ
        if (reg.Flags & 0x40) {
            reg.PC = reg.SP.pop(memory) | (reg.SP.pop(memory) << 8);
        }
        else {
            reg.PC++;
        }
        break;
    }

    // === SBB ===

    case 0x9F: { // SBB A
        uint8_t prev = reg.A;
        reg.A = ALU::sbi(reg, reg.A);
        reg.PC++;
        message("Reg A:", reg.A, 0, MessageType::REGISTER);
        message("SBB A executed. [A] <- [A] - [A] - CY", reg.A, prev, MessageType::REGISTER);
    }
    case 0x98: { // SBB B
        uint8_t prev = reg.A;
        reg.A = ALU::sbi(reg, reg.B);
        reg.PC++;
        message("Reg B:", reg.B, 0, MessageType::REGISTER);
        message("SBB B executed. [A] <- [A] - [B] - CY", reg.A, prev, MessageType::REGISTER);
        [[fallthrough]];
        break;
    }

    case 0x99: { // SBB C
        uint8_t prev = reg.A;
        reg.A = ALU::sbi(reg, reg.C);
        reg.PC++;
        message("Reg C:", reg.C, 0, MessageType::REGISTER);
        message("SBB C executed. [A] <- [A] - [C] - CY", reg.A, prev, MessageType::REGISTER);
        break;
    }

    case 0x9A: { // SBB D
        uint8_t prev = reg.A;
        reg.A = ALU::sbi(reg, reg.D);
        reg.PC++;
        message("Reg D:", reg.D, 0, MessageType::REGISTER);
        message("SBB D executed. [A] <- [A] - [D] - CY", reg.A, prev, MessageType::REGISTER);
        break;
    }

    case 0x9B: { // SBB E
        uint8_t prev = reg.A;
        reg.A = ALU::sbi(reg, reg.E);
        reg.PC++;
        message("Reg E:", reg.E, 0, MessageType::REGISTER);
        message("SBB E executed. [A] <- [A] - [E] - CY", reg.A, prev, MessageType::REGISTER);
        break;
    }

    case 0x9C: { // SBB H
        uint8_t prev = reg.A;
        reg.A = ALU::sbi(reg, reg.H);
        reg.PC++;
        message("Reg H:", reg.H, 0, MessageType::REGISTER);
        message("SBB H executed. [A] <- [A] - [H] - CY", reg.A, prev, MessageType::REGISTER);
        break;
    }

    case 0x9D: { // SBB L
        uint8_t prev = reg.A;
        reg.A = ALU::sbi(reg, reg.L);
        reg.PC++;
        message("Reg L:", reg.L, 0, MessageType::REGISTER);
        message("SBB L executed. [A] <- [A] - [L] - CY", reg.A, prev, MessageType::REGISTER);
        break;
    }

    case 0x9E: { // SBB M
        uint8_t prev = reg.A;
        reg.A = ALU::sbi(reg, memory.read(reg.HL.get()));
        reg.PC++;
        message("Reg H:", reg.H, 0, MessageType::REGISTER);
        message("SBB M executed. [A] <- [A] - [M] - CY", reg.A, prev, MessageType::REGISTER);
        break;
    }



    // === SBI ===

    case 0xDE: { // SBI
        uint8_t value = memory.read(++reg.PC);
        reg.A = ALU::sbi(reg, value);
        reg.PC++;
        message("Immediate Value:", value, 0, MessageType::REGISTER);
        message("SBI executed. [A] <- [A] - value - CY", reg.A, 0, MessageType::REGISTER);
        break;
    }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       

    // === Misc... ===

    case 0x22: { // SHLD
        reg.PC++;
        uint16_t address = (memory.read(reg.PC++) | (memory.read(reg.PC++) << 8));
		uint8_t data = reg.HL.get() & 0xFF;
		memory.write(address, data);
		uint8_t data2 = (reg.HL.get() >> 8) & 0xFF;
		memory.write(address + 1, data2);
        //debug("SHLD executed: address = [H-L] == ", reg.HL.get(),0, MessageType::REGISTER);
        t2t_message("SHLD executed.", address, data, Type2Tpe::t16_2_8);
        t2t_message("", address + 1, data2, Type2Tpe::t16_2_8);
        break;
    }
    case 0x30: { // SIM 
        interruptControl.setMask(reg.A);
        reg.PC++;
		message("SIM executed. In <- [A] : ", reg.A, 0, MessageType::REGISTER);
        break;
    }
    case 0xF9: { // SPHL 
        reg.SP = static_cast<uint16_t>(reg.HL.get());
        reg.PC++;
		message("SPHL executed. HL <- SP: ", reg.SP & 0xFF, reg.SP >> 8, MessageType::REGISTER);
        break;
    }
    case 0x32: { // STA 
        reg.PC++;
        uint16_t address = memory.read(reg.PC++) | (memory.read(reg.PC++) << 8);
        memory.write(address, reg.A);
		debug("STA executed. [ADDR] : ", address, reg.A, MessageType::MEMORY);
        break;
    }
    case 0x02: { // STAX B
        memory.write(reg.BC.get(), reg.A);
        reg.PC++;
		debug("STAX B executed. [BC] : ", reg.BC.get(), reg.A, MessageType::MEMORY);
        break;
    }
    case 0x12: { // STAX D
        memory.write(reg.DE.get(), reg.A);
        reg.PC++;
		debug("STAX D executed. [DE] : ", reg.DE.get(), reg.A, MessageType::MEMORY);
        break;
    }
    case 0x37: { // STC
        reg.Flags |= 0x01;
        reg.PC++;
		message("STC executed. Carry flag set.", 0, 0, MessageType::REGISTER);
        break;
    }

    // === SUB ===

    case 0x97: { // SUB A
        uint8_t prev = reg.A;
        reg.A = ALU::sub(reg, reg.A);
        reg.PC++;
        message("Reg A: ", reg.A, 0, MessageType::REGISTER);
        message("SUB A executed. [A] <- [A]", reg.A, prev, MessageType::REGISTER);
        break;
    }
    case 0x90: { // SUB B
        uint8_t prev = reg.A;
        reg.A = ALU::sub(reg, reg.B);
        reg.PC++;
        message("Reg B: ", reg.B, 0, MessageType::REGISTER);
        message("SUB B executed. [A] <- [A]", reg.A, prev, MessageType::REGISTER);
        break;
    }
    case 0x91: { // SUB C
        uint8_t prev = reg.A;
        reg.A = ALU::sub(reg, reg.C);
        reg.PC++;
        message("Reg C: ", reg.C, 0, MessageType::REGISTER);
        message("SUB C executed. [A] <- [A]", reg.A, prev, MessageType::REGISTER);
        break;
    }
    case 0x92: { // SUB D
        uint8_t prev = reg.A;
        reg.A = ALU::sub(reg, reg.D);
        reg.PC++;
        message("Reg D: ", reg.D, 0, MessageType::REGISTER);
        message("SUB D executed. [A] <- [A]", reg.A, prev, MessageType::REGISTER);
        break;
    }
    case 0x93: { // SUB E
        uint8_t prev = reg.A;
        reg.A = ALU::sub(reg, reg.E);
        reg.PC++;
        message("Reg E: ", reg.E, 0, MessageType::REGISTER);
        message("SUB C executed. [A] <- [A]", reg.A, prev, MessageType::REGISTER);
        break;
    }
    case 0x94: { // SUB H
        uint8_t prev = reg.A;
        reg.A = ALU::sub(reg, reg.H);
        reg.PC++;
        message("Reg E: ", reg.E, 0, MessageType::REGISTER);
        message("SUB H executed. [A] <- [A]", reg.A, prev, MessageType::REGISTER);
        break;
    }
    case 0x95: { // SUB L
        uint8_t prev = reg.A;
        reg.A = ALU::sub(reg, reg.L);
        reg.PC++;
        message("Reg L: ", reg.L, 0, MessageType::REGISTER);
        message("SUB L executed. [A] <- [A]", reg.A, prev, MessageType::REGISTER);
        break;
    }
    case 0x96: { // SUB M
        uint8_t prev = reg.A;
        reg.A = ALU::sub(reg, memory.read(reg.HL.get()));
        reg.PC++;
        message("Reg M: ", memory.read(reg.HL.get()), 0, MessageType::REGISTER);
        message("SUB M executed. [A] <- [A]", reg.A, prev, MessageType::REGISTER);
        break;
    }

    // === SUI ===

    case 0xD6: { // SUI 
        reg.PC++;
        uint8_t prev = reg.A;
        uint8_t value = memory.read(reg.PC++);
        reg.A = ALU::sub(reg, value);
        message("Immediate Value ", value, 0, MessageType::REGISTER);
        message("SUI executed. [A] <- [A]", reg.A, prev, MessageType::REGISTER);
        break;
    }

    // === XCHG ===

    case 0xEB: { // XCHG (HL <-> DE)
        uint16_t temp = reg.HL.get();
        reg.HL.set(reg.DE.get());
		reg.H = reg.HL.get() >> 8;
		reg.L = reg.HL.get() & 0xFF;
        reg.DE.set(temp);
		reg.D = reg.DE.get() >> 8;
		reg.E = reg.DE.get() & 0xFF;
        reg.PC++;
        t2t_message("XCHG executed. [HL] <-> [DE]", reg.HL.get(), reg.DE.get(), Type2Tpe::t16_2_16);
        break;
    }

    // === XRA ===

    case 0xAF: { // XRA A
        uint8_t prev = reg.A;
        reg.A = ALU::xra(reg, reg.A);
        reg.PC++;
        t2t_message("XRA A executed. [A] <- [A]", reg.A, prev, Type2Tpe::t8_2_8);
        break;
    }
    case 0xA8: { // XRA B
        uint8_t prev = reg.A;
        reg.A = ALU::xra(reg, reg.B);
        reg.PC++;
        t2t_message("XRA B executed. [A] <- [A]", reg.A, prev, Type2Tpe::t8_2_8);
        break;
    }
    case 0xA9: { // XRA C
        uint8_t prev = reg.A;
        reg.A = ALU::xra(reg, reg.C);
        reg.PC++;
        t2t_message("XRA C executed. [A] <- [A]", reg.A, prev, Type2Tpe::t8_2_8);
        break;
    }
    case 0xAA: { // XRA D
        uint8_t prev = reg.A;
        reg.A = ALU::xra(reg, reg.D);
        reg.PC++;
        t2t_message("XRA D executed. [A] <- [A]", reg.A, prev, Type2Tpe::t8_2_8);
        break;
    }
    case 0xAB: { // XRA E
        uint8_t prev = reg.A;
        reg.A = ALU::xra(reg, reg.E);
        reg.PC++;
        t2t_message("XRA E executed. [A] <- [A]", reg.A, prev, Type2Tpe::t8_2_8);
        break;
    }
    case 0xAC: { // XRA H
        uint8_t prev = reg.A;
        reg.A = ALU::xra(reg, reg.H);
        reg.PC++;
        t2t_message("XRA H executed. [A] <- [A]", reg.A, prev, Type2Tpe::t8_2_8);
        break;
    }
    case 0xAD: { // XRA L
        uint8_t prev = reg.A;
        reg.A = ALU::xra(reg, reg.L);
        reg.PC++;
        t2t_message("XRA L executed. [A] <- [A]", reg.A, prev, Type2Tpe::t8_2_8);
        break;
    }
    case 0xAE: { // XRA M 
        uint8_t prev = reg.A;
        reg.A = ALU::xra(reg, memory.read(reg.HL.get()));
        reg.PC++;
        t2t_message("XRA H executed. [A] <- [A]", reg.A, prev, Type2Tpe::t8_2_8);
        break;
    }
    case 0xEE: { // XRI 
        uint8_t prev = reg.A;
        reg.PC++;
        reg.A = ALU::xra(reg, memory.read(reg.PC++));
        t2t_message("XRI executed. [A] <- [A]", reg.A, prev, Type2Tpe::t8_2_8);
        break;
    }

    // === XTHL ===

    case 0xE3: { // XTHL (Exchange Top of Stack with HL)
        uint8_t tempL = memory.read(reg.SP.get());
        uint8_t tempH = memory.read(reg.SP.get() + 1);
        memory.write(reg.SP.get(), reg.L);
        memory.write(reg.SP.get() + 1, reg.H);
        reg.L = tempL;
        reg.H = tempH;
        reg.PC++;
        break;
    }

    // === IN / OUT ===

    case 0xDB: { // IN 
        reg.PC++;
        uint8_t portAddress = memory.read(reg.PC++);
        reg.A = io.read(portAddress); 
        break;
    }
    //case 0xD3: { // OUT 
    //    reg.PC++;
    //    uint8_t portAddress = memory.read(reg.PC++);
    //    io.write(portAddress, reg.A); 
    //    break;
    //}

    case 0xD3: { // OUT 
        reg.PC++;
        uint8_t value = memory.read(reg.PC++);
        //uint8_t portAddress = memory.read(reg.PC++);
        //io.write(portAddress, reg.A);
        //message("OUT : ", value, reg.A, MessageType::REGISTER);
        t2t_message("OUT executed. [Port] <- [A]: ", value, reg.A, Type2Tpe::t8_2_8);
        break;
    }

    case 0x76:
        debug("HLT", opcode, 0, MessageType::INFO);
        reg.PC++;
        isHalt = true;
        return -1;

    default:
        std::cout << "Unknown Opcode: " << std::hex << static_cast<int>(opcode) << std::endl;
    }



    return 0;
}

