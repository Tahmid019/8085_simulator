#include "Head_1.h"
#include "utils.h"
#include "CPU.h"
#include "IOHandler.h"

class sim_8085 {
private:
    CPU cpu;
    IOHandler io_handler;
public:
    sim_8085() {
        cpu.reg.A = 0x00;
        cpu.reg.B = 0x00;
        cpu.reg.C = 0x00;
        cpu.reg.D = 0x00;
        cpu.reg.E = 0x00;
        cpu.reg.H = 0x00;
        cpu.reg.L = 0x00;
        cpu.reg.PC = 0x0000;
        cpu.reg.SP = 0x0000;
        cpu.reg.Flags = 0x00;
    }
    void load_program(string filename, bool debug = false) {
        message("Loading Program in Main Memory ...", 0, 0, MessageType::INFO);
        io_handler.loadProgram(filename, cpu);
    }
    void execute_program(uint16_t init_addr) {
        message("Executing Program from Main Memory ...", 0, 0, MessageType::INFO);
        while (true) {
            int check = cpu.execute(cpu.memory.read(init_addr++));
            if (check == -1) break;
            cout << endl;
        }
    }
};

int main() {

    sim_8085 instance;
    instance.load_program("program.txt", false);
    instance.execute_program(0);

    return 0;
}
