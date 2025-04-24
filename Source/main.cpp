#include "../Headers/Head_1.h"
#include "../Headers/utils.h"
#include "../Headers/CPU.h"
#include "../Headers/IOHandler.h"
#include "../Headers/Parser.h"

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
        cpu.reg.BC.set(0x0000);
        cpu.reg.DE.set(0x0000);
        cpu.reg.HL.set(0x0000);
        cpu.reg.PC = 0x0000;
        cpu.reg.SP = 0xffff;
        cpu.reg.Flags = 0x00;
    }
	void input_data() {
		message("Insert data in Memory ...", 0, 0, MessageType::INFO);
		io_handler.initializeData2Memory(cpu);
	}
    void load_program(string filename,uint16_t init_addr, bool debug = false) {
        message("Loading Program in Main Memory ...", 0, 0, MessageType::INFO);
        io_handler.loadProgram(cpu, filename, init_addr);
    }
    void execute_program(uint16_t init_addr) {
        message("Executing Program from Main Memory ...", 0, 0, MessageType::INFO);
        cpu.reg.PC = init_addr;
        while (true) {
            int check = cpu.execute(cpu.memory.read(cpu.reg.PC));
            if (check == -1) break;
            cout << endl;
        }
    }
    ~sim_8085() {
        cerr << "sim_8085 instance deconstructed" << endl;
    }
};

int main() {
    try {
        uint16_t start_addr = 0x0000;
	    string filename = "program.txt";
        filename = R"(..\..\..\Source\)" + filename;

        sim_8085 instance;
	    instance.input_data();
        instance.load_program(filename, start_addr, false);
        instance.execute_program(start_addr); 
    }
    catch (const invalid_argument& e) {
        cerr << "Argument error: " << e.what() << endl;
        return 1;
    }
    catch (const out_of_range& e) {
        cerr << "Out-of-range error: " << e.what() << endl;
        return 2;
    }
    catch (const exception& e) {
        cerr << "Unhandled exception: " << e.what() << endl;
        return 3;
    }
    catch (...) {
        cerr << "Unknown fatal error\n";
        return 4;
    }

    return 0;
}
