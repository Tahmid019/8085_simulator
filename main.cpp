#include "CPU.h"
#include "IOHandler.h"
#include <iostream>

int main() {
    CPU cpu;
    IOHandler::loadProgram("program.txt", cpu);
    for (int i = 0; i < 5; i++) {  
        cpu.execute(cpu.memory.read(i));
    }
    std::cout << "Register A: " << std::hex << (int)cpu.reg.A << std::endl;
    return 0;
}
