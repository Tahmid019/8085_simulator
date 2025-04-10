#include "Head_1.h"
#include "Memory.h"

void Memory::write(uint16_t address, uint8_t data) {
    mem[address] = data;
    std::cout << "Memory[" << std::hex << address << "] = " << static_cast<int>(data) << std::endl;
}
uint8_t Memory::read(uint16_t address) {
    std::cout << "Reading Memory[" << std::hex << address << "]: " << static_cast<int>(mem[address]) << std::endl;
    return mem[address];
}
void Memory::clear() {
	mem.clear();
	std::cout << "Memory Cleared" << std::endl;
}