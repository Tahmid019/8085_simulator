#include "utils.h"

void message(std::string msg="", uint8_t in_load=0x00, uint8_t out_load=0x00) {
    std::string prefix;
    MessageType type = MessageType::INFO;
    switch (type) {
    case MessageType::INFO: {
        prefix = "[INFO] ";
        std::cout << prefix << msg << std::endl;
        break;
    }
    case MessageType::WARNING: {
        prefix = "[WARNING] ";
        std::cout << prefix << msg << std::endl;
        break;
    }
    case MessageType::ERROR:   prefix = "[ERROR] ";   break;
    case MessageType::MEMORY: {
        prefix = "[MEMORY - Load] ";
        std::cerr << prefix << msg << " Memory-value: [ " << static_cast<int>(in_load) << " ]";
        break;
    }
    case MessageType::REGISTER: {
        prefix = "[REGISTER - Load] ";
        std::cerr << prefix << msg << " Register-value: [ " << static_cast<int>(in_load) << " ]";
        break;
    }
    }   

    if (out_load != 0x00) std::cout << " <-- [ " << static_cast<int>(out_load) << " ]";
    std::cout << std::endl;
}

bool parity(uint8_t val) {
    int count_1s = 0;
    int count_0s = 0;

    ((val & 0x10000000) == 0x10000000) ? count_1s++ : count_0s++;
    ((val & 0x01000000) == 0x01000000) ? count_1s++ : count_0s++;
    ((val & 0x00100000) == 0x00100000) ? count_1s++ : count_0s++;
    ((val & 0x00010000) == 0x00010000) ? count_1s++ : count_0s++;
    ((val & 0x00001000) == 0x00001000) ? count_1s++ : count_0s++;
    ((val & 0x00000100) == 0x00000100) ? count_1s++ : count_0s++;
    ((val & 0x00000010) == 0x00000010) ? count_1s++ : count_0s++;
    ((val & 0x00000001) == 0x00000001) ? count_1s++ : count_0s++;

    if (count_1s % 2 == 0) return true;
    return false;
}

bool auxillaryCarry(uint8_t regValue_1, uint8_t regValue_2) {
    return ((regValue_1 & 0x00001000) && (regValue_2 & 0x00001000));
}

bool carry(uint8_t value) {
    return (((int)value / 255) != 0);
}
