#include "../Headers/Head_1.h"
#include "../Headers/Memory.h"

Memory::Memory() {
    mem.resize(65536, 0);
   /* for (uint16_t i = 0; i < UINT16_MAX; i++) {
        mem[i] = static_cast<uint16_t>(-1);
    }*/
}

void Memory::write(uint16_t address, uint8_t data) {
    mem[address] = data;
    std::cout << "Memory{" << std::hex << address << "} = " << static_cast<int>(data) << std::endl;
}
uint8_t Memory::read(uint16_t address) {
    std::cout << "Reading Memory[" << std::hex << address << "]: " << static_cast<int>(mem[address]) << std::endl;
    return mem[address];
}
void Memory::clear() {
	mem.vector::clear();
    mem.vector::resize(65536, 0);
	std::cout << "Memory Cleared" << std::endl;
}