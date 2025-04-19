#include "../Headers/Head_1.h"
#include "../Headers/IOHandler.h"
#include "../Headers/Instructions.h"
#include "../Headers/utils.h"

void IOHandler::initializeData2Memory(CPU& cpu) {
    cout << "[ Insert data in Memory ] / [ Press 2 to Run Anyway ] :\n";
    while (true) {
        string a, b;cin >> a;
        if (a == "2")break;
        cin >> b;
        int address = stoi(a, 0, 16);
        int val = stoi(b);
        cpu.memory.write(address, val);
    }
}

void IOHandler::loadProgram(CPU& cpu, string filename, uint16_t& init_addr) {
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "Error: Cant Open the File ... " << filename << std::endl;
        exit(1);
        return;
    }

    uint16_t addr = init_addr;
    std::string strInst;
    int ws = 0;

    while (getline(file, strInst)) {
        removeTrailingSpaces(strInst);
        if (ws>0) {
            cpu.memory.write(addr++, stoi(strInst)); // STRING TO HEXT IMPLEMENTATION
            debug("Loaded at: ", addr - 1, 0, MessageType::MEMORY);
            ws--;
            continue;
        }
        if (strInst == "") continue;
        if (instructionSet.find(strInst) == instructionSet.end()) {
            std::cerr << "Error: {" << strInst << "} | Invalid Instruction ..." << std::endl;
            exit(1);
        }

        Instruction Inst = instructionSet[strInst];
        uint8_t oc = Inst.opcode;
        ws = Inst.wordSize;

        switch (ws) {
            case 1: {
                cpu.memory.write(addr++, oc);
                ws--;
                debug("Loaded at: ", addr-1, oc, MessageType::MEMORY);
                break;
            }
        
            case 2: {
                cpu.memory.write(addr++, oc);
                ws--;
                debug("Loaded at: ", addr - 1, 0, MessageType::MEMORY);
                break;
            }
            
            case 3: {
                cpu.memory.write(addr++, oc);
                ws--;
                debug("Loaded at: ", addr - 1, 0, MessageType::MEMORY);
                break;
            }

            default: {
                debug("Invalid IO case", 0, 0, MessageType::INFO);
                exit(1);
            }
        }
    }

    file.close();
}


