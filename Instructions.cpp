#include "Instructions.h"
#include "utils.h"
#include <iostream>

std::unordered_map<std::string, Instruction> instructionSet = {
    {"ACI", Instruction("ACI", 0xCE, 2)},
    
    {"ADC A", Instruction("ADC A", 0x8F, 1)},
    {"ADC B", Instruction("ADC B", 0x88, 1)},
    {"ADC C", Instruction("ADC C", 0x89, 1)},
    {"ADC D", Instruction("ADC D", 0x8A, 1)},
    {"ADC E", Instruction("ADC E", 0x8B, 1)},
    {"ADC H", Instruction("ADC H", 0x8C, 1)},
    {"ADC L", Instruction("ADC L", 0x8D, 1)},
    {"ADC M", Instruction("ADC M", 0x8E, 1)},
    
    {"ADD A", Instruction("ADD A", 0x87, 1)},
    {"ADD B", Instruction("ADD B", 0x80, 1)},
    {"ADD C", Instruction("ADD C", 0x81, 1)},
    {"ADD D", Instruction("ADD D", 0x82, 1)},
    {"ADD E", Instruction("ADD E", 0x83, 1)},
    {"ADD H", Instruction("ADD H", 0x84, 1)},
    {"ADD L", Instruction("ADD L", 0x85, 1)},
    {"ADD M", Instruction("ADD M", 0x86, 1)},

    {"ADI", Instruction("ADI", 0xC6, 2)},
    
    {"ANA A", Instruction("ANA A", 0xA7, 1)},
    {"ANA B", Instruction("ANA B", 0xA0, 1)},
    {"ANA C", Instruction("ANA C", 0xA1, 1)},
    {"ANA D", Instruction("ANA D", 0xA2, 1)},
    {"ANA E", Instruction("ANA E", 0xA3, 1)},
    {"ANA H", Instruction("ANA H", 0xA4, 1)},
    {"ANA L", Instruction("ANA L", 0xA5, 1)},
    {"ANA M", Instruction("ANA M", 0xA6, 1)},
    
    {"ANI", Instruction("ANI", 0xE6, 2)},
    
    {"CALL", Instruction("CALL", 0xCD, 3)},
    {"CC", Instruction("CC", 0xDC, 3)},
    {"CM", Instruction("CM", 0xFC, 3)},
    {"CMA", Instruction("CMA", 0x2F, 1)},
    {"CMC", Instruction("CMC", 0x3F, 1)},
    
    {"CMP A", Instruction("CMP A", 0xBF, 1)},
    {"CMP B", Instruction("CMP B", 0xB8, 1)},
    {"CMP C", Instruction("CMP C", 0xB9, 1)},
    {"CMP D", Instruction("CMP D", 0xBA, 1)},
    {"CMP E", Instruction("CMP E", 0xBB, 1)},
    {"CMP H", Instruction("CMP H", 0xBC, 1)},
    {"CMP L", Instruction("CMP L", 0xBD, 1)},
    {"CMP M", Instruction("CMP M", 0xBD, 1)},
    
    {"CNC", Instruction("CNC", 0xD4, 3)},
    {"CNZ", Instruction("CNZ", 0xC4, 3)},
    {"CP", Instruction("CP", 0xF4, 3)},
    {"CPE", Instruction("CPE", 0xEC, 3)},
    {"CPI", Instruction("CPI", 0xFE, 2)},
    {"CPO", Instruction("CPO", 0xE4, 3)},
    {"CZ", Instruction("CZ", 0xCC, 3)},
    
    {"DAA", Instruction("DAA", 0x27, 1)},
    
    {"DAD B", Instruction("DAD B", 0x09, 1)},
    {"DAD D", Instruction("DAD D", 0x19, 1)},
    {"DAD H", Instruction("DAD H", 0x29, 1)},
    {"DAD SP", Instruction("DAD SP", 0x39, 1)},
    
    {"DCR A", Instruction("DCR A", 0x3D, 1)},
    {"DCR B", Instruction("DCR B", 0x05, 1)},
    {"DCR C", Instruction("DCR C", 0x0D, 1)},
    {"DCR D", Instruction("DCR D", 0x15, 1)},
    {"DCR E", Instruction("DCR E", 0x1D, 1)},
    {"DCR H", Instruction("DCR H", 0x25, 1)},
    {"DCR L", Instruction("DCR L", 0x2D, 1)},
    {"DCR M", Instruction("DCR M", 0x35, 1)},

    {"DCX B", Instruction("DCX B", 0x0B, 1)},
    {"DCX D", Instruction("DCX D", 0x1B, 1)},
    {"DCX H", Instruction("DCX H", 0x22B, 1)},
    {"DCX SP", Instruction("DCX SP", 0x3B, 1)},

    {"DI", Instruction("DI", 0xF3, 1)},
    {"EI", Instruction("EI", 0xFB, 1)},

    {"INR A", Instruction("INR A", 0x3C, 1)},
    {"INR B", Instruction("INR B", 0x04, 1)},
    {"INR C", Instruction("INR C", 0x0C, 1)},
    {"INR D", Instruction("INR D", 0x14, 1)},
    {"INR E", Instruction("INR E", 0x1C, 1)},
    {"INR H", Instruction("INR H", 0x24, 1)},
    {"INR L", Instruction("INR L", 0x2C, 1)},
    {"INR M", Instruction("INR M", 0x34, 1)},

    {"INX B", Instruction("INX B", 0x03, 1)},
    {"INX D", Instruction("INX D", 0x13, 1)},
    {"INX H", Instruction("INX H", 0x23, 1)},
    {"INX SP", Instruction("INX SP", 0x33, 1)},

    {"MOV A, A", Instruction("MOV A, A", 0x7F, 1)},
    {"MOV A, B", Instruction("MOV A, B", 0x78, 1)},
    {"MOV A, C", Instruction("MOV A, C", 0x79, 1)},
    {"MOV A, D", Instruction("MOV A, D", 0x7A, 1)},
    {"MOV A, E", Instruction("MOV A, E", 0x7B, 1)},
    {"MOV A, H", Instruction("MOV A, H", 0x7C, 1)},
    {"MOV A, L", Instruction("MOV A, L", 0x7D, 1)},
    {"MOV A, M", Instruction("MOV A, M", 0x7E, 1)},

    {"MOV B, A", Instruction("MOV B, A", 0x47, 1)},
    {"MOV B, B", Instruction("MOV B, B", 0x40, 1)},
    {"MOV B, C", Instruction("MOV B, C", 0x41, 1)},
    {"MOV B, D", Instruction("MOV B, D", 0x42, 1)},
    {"MOV B, E", Instruction("MOV B, E", 0x43, 1)},
    {"MOV B, H", Instruction("MOV B, H", 0x44, 1)},
    {"MOV B, L", Instruction("MOV B, L", 0x45, 1)},
    {"MOV B, M", Instruction("MOV B, M", 0x46, 1)},

    {"MOV C, A", Instruction("MOV C, A", 0x4F, 1)},
    {"MOV C, B", Instruction("MOV C, B", 0x48, 1)},
    {"MOV C, C", Instruction("MOV C, C", 0x49, 1)},
    {"MOV C, D", Instruction("MOV C, D", 0x4A, 1)},
    {"MOV C, E", Instruction("MOV C, E", 0x4B, 1)},
    {"MOV C, H", Instruction("MOV C, H", 0x4C, 1)},
    {"MOV C, L", Instruction("MOV C, L", 0x4D, 1)},
    {"MOV C, M", Instruction("MOV C, M", 0x4E, 1)},

    {"MOV D, A", Instruction("MOV D, A", 0x57, 1)},
    {"MOV D, B", Instruction("MOV D, B", 0x50, 1)},
    {"MOV D, C", Instruction("MOV D, C", 0x51, 1)},
    {"MOV D, D", Instruction("MOV D, D", 0x52, 1)},
    {"MOV D, E", Instruction("MOV D, E", 0x53, 1)},
    {"MOV D, H", Instruction("MOV D, H", 0x54, 1)},
    {"MOV D, L", Instruction("MOV D, L", 0x55, 1)},
    {"MOV D, M", Instruction("MOV D, M", 0x56, 1)},

    {"MOV E, A", Instruction("MOV E, A", 0x5F, 1)},
    {"MOV E, B", Instruction("MOV E, B", 0x58, 1)},
    {"MOV E, C", Instruction("MOV E, C", 0x59, 1)},
    {"MOV E, D", Instruction("MOV E, D", 0x5A, 1)},
    {"MOV E, E", Instruction("MOV E, E", 0x5B, 1)},
    {"MOV E, H", Instruction("MOV E, H", 0x5C, 1)},
    {"MOV E, L", Instruction("MOV E, L", 0x5D, 1)},
    {"MOV E, M", Instruction("MOV E, M", 0x5E, 1)},

    {"MVI A",    Instruction("MVI A"   , 0x3E, 2)},
    {"MVI B",    Instruction("MVI B"   , 0x06, 2)},
    {"MVI C",    Instruction("MVI C"   , 0x0E, 2)},
    {"MVI D",    Instruction("MVI D"   , 0x16, 2)},
    {"MVI E",    Instruction("MVI E"   , 0x1E, 2)},
    {"MVI H",    Instruction("MVI H"   , 0x26, 2)},
    {"MVI L",    Instruction("MVI L"   , 0x2E, 2)},
    {"MVI M",    Instruction("MVI M"   , 0x36, 2)},

    {"IN", Instruction("IN", 0xDB, 2)},
    {"OUT B",    Instruction("OUT B"   , 0xD3, 1)},

    {"HLT",      Instruction("HLT"     , 0x76, 1)},
};

std::unordered_map<std::string, std::function<void()>> instructionHandlers = {
    {"MVI A", [] { debug("MVI A", 0); }}
};
