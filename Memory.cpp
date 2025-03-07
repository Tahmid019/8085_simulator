#include "Memory.h"
#include <iostream>

void Memory::write(uint16_t address, uint8_t data) {
    mem[address] = data;
    std::cout << "Memory[" << std::hex << address << "] = " << (int)data << std::endl;
}
uint8_t Memory::read(uint16_t address) {
    std::cout << "Reading Memory[" << std::hex << address << "]: " << (int)mem[address] << std::endl;
    return mem[address];
}
