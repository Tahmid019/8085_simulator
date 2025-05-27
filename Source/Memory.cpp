#include "../Headers/Head_1.h"
#include "../Headers/Memory.h"
#include "../Headers/utils.h"

Memory::Memory() {
    mem.resize(65536, 0);
}

void Memory::loadMemory(const std::string& mem_file) {
    std::ifstream file(mem_file);
    if (!file.is_open()) {
        throw std::runtime_error("memory.csv not found");
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == ';') continue;

        std::stringstream ss(line);
        uint16_t addr;
        uint8_t  val;
        char     comma;

        if (!(ss >> addr >> comma >> val)) {
            std::cerr << "Skipping malformed line: " << line << "\n";
            continue;
        }

        if (addr < mem.size()) {
            mem[addr] = val;
            t2t_message("Memory: ", addr, val, Type2Tpe::t16_2_8);
        }
    }
}

void Memory::write(uint16_t address, uint8_t data) {
    mem[address] = data;
    cout << "Memory{" << hex << address << "} = " << static_cast<int>(data) << endl;
}
uint8_t Memory::read(uint16_t address) {
    cout << "Reading Memory[" << hex << address << "]: " << static_cast<int>(mem[address]) << endl;
    return mem[address];
}
void Memory::clear() {
	mem.vector::clear();
    mem.vector::resize(65536, 0);
	//cout << "Memory Cleared" << endl;
}

void Memory::save2csv(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << " for writing.\n";
        return;
    }

    for (uint16_t address = 0; address < mem.size(); ++address) {
        if (mem[address] != 0) {  
            file << address << "," << mem[address] << "\n";
        }
    }

    file.close();
}
