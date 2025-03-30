#include "CPU.h"
#include "IOHandler.h"
#include <iostream>

int main() {
    CPU cpu;

    std::cout << "\nLoading Prog ...\n" << std::endl;
    IOHandler::loadProgram("program.txt", cpu);
    
    std::cout << "\nExecuting Prog ... \n" << std::endl;
    int i = 0;
    while (1) {
        int check = cpu.execute(cpu.memory.read(i++));
        if (check == -1) break;
        std::cout << std::endl;
    }

    return 0;
}
