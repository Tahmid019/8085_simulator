#include "utils.h"

void debug(std::string mn, uint8_t reg) {
    std::cerr << mn << " executed. [" << std::hex << (int)reg << "]" << std::endl;
}

void message(std::string msg, uint8_t mem) {
    std::cerr << msg << " [ " << mem << " ]" << std::endl;
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
