#include "CPU.h"
#include "IOHandler.h"
#include <iostream>

int main() {
    CPU cpu;
    IOHandler::loadProgram("program.txt", cpu);
    
    int i = 0;
    while (1) {
        std::cerr << i << std::endl;
        int check = cpu.execute(cpu.memory.read(i++));
        if (check == -1) break;
    }

    return 0;
}
