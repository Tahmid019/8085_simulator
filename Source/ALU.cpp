#include "../Headers/Head_1.h"
#include "../Headers/ALU.h"
#include "../Headers/utils.h"

/*

	FLAG: Sgn - Z - P - AC C 

*/

namespace {
    constexpr uint8_t F_S = 0x80;  
    constexpr uint8_t F_Z = 0x20;  
    constexpr uint8_t F_P = 0x08;  
    constexpr uint8_t F_AC = 0x02;  
    constexpr uint8_t F_C = 0x01;  

    constexpr uint8_t MASK_SZPAC = F_S | F_Z | F_P | F_AC | F_C;
    constexpr uint8_t MASK_SZP = F_S | F_Z | F_P;
}

uint8_t ALU::add(Registers& reg, uint8_t value) {
    uint16_t sum = uint16_t(reg.A) + value;
    uint8_t  r = uint8_t(sum);

    uint8_t newF = 0;
    if (r & 0x80) newF |= F_S;
    if (r == 0) newF |= F_Z;
    if (parity<uint8_t>(r)) newF |= F_P;
    if (auxiliaryCarry<uint8_t>(reg.A, value)) newF |= F_AC;
    if (sum > 0xFF) newF |= F_C;

    reg.A = r;
    reg.Flags = (reg.Flags & ~MASK_SZPAC) | newF;
    return r;
}

uint8_t ALU::adc(Registers& reg, uint8_t value) {
    uint8_t  carryIn = (reg.Flags & F_C) ? 1 : 0;
    uint16_t sum = uint16_t(reg.A) + value + carryIn;
    uint8_t  r = uint8_t(sum);

    uint8_t newF = 0;
    if (r & 0x80)  newF |= F_S;
    if (r == 0)  newF |= F_Z;
    if (parity<uint8_t>(r)) newF |= F_P;
    if (auxiliaryCarry<uint8_t>(reg.A, value + carryIn)) newF |= F_AC;
    if (sum > 0xFF)newF |= F_C;

    reg.A = r;
    reg.Flags = (reg.Flags & ~MASK_SZPAC) | newF;
    return r;
}

uint8_t ALU::sub(Registers& reg, uint8_t value) {
    uint8_t  a0 = reg.A;
    uint16_t diff = uint16_t(a0) - value;
    uint8_t  r = uint8_t(diff);

    uint8_t newF = 0;
    if (r & 0x80)newF |= F_S;
    if (r == 0) newF |= F_Z;
    if (parity<uint8_t>(r)) newF |= F_P;
    if ((a0 & 0x0F) < (value & 0x0F)) newF |= F_AC;
    if (a0 < value)  newF |= F_C;

    reg.A = r;
    reg.Flags = (reg.Flags & ~MASK_SZPAC) | newF;
    return r;
}

uint8_t ALU::sbi(Registers& reg, uint8_t value) {
    uint8_t borrow = (reg.Flags & F_C) ? 1 : 0;
    uint8_t result = sub(reg, value + borrow);
    return result;
}

uint8_t ALU::cmp(Registers& reg, uint8_t value) {
    uint8_t  a0 = reg.A;
    uint8_t  result = a0 - value;

    uint8_t newF = 0;
    if (result & 0x80)         newF |= F_S;
    if (result == 0)           newF |= F_Z;
    if (parity<uint8_t>(result)) newF |= F_P;
    if ((a0 & 0x0F) < (value & 0x0F)) newF |= F_AC;
    if (a0 < value)            newF |= F_C;

    reg.Flags = (reg.Flags & ~MASK_SZPAC) | newF;
    return result;
}

uint8_t ALU::ana(Registers& reg, uint8_t value) {
    uint8_t r = reg.A & value;
  
    uint8_t newF = 0;
    if (r & 0x80)             newF |= F_S;
    if (r == 0)               newF |= F_Z;
    if (parity<uint8_t>(r))     newF |= F_P;
    if ((reg.A | value) & 0x08) newF |= F_AC;
    // C = 0

    reg.A = r;
    reg.Flags = (reg.Flags & ~MASK_SZPAC) | newF;
    return r;
}

uint8_t ALU::ora(Registers& reg, uint8_t value) {
    uint8_t r = reg.A | value;

    uint8_t newF = 0;
    if (r & 0x80)             newF |= F_S;
    if (r == 0)               newF |= F_Z;
    if (parity<uint8_t>(r))     newF |= F_P;
    //always clears AC and C

    reg.A = r;
    reg.Flags = (reg.Flags & ~MASK_SZPAC) | newF;
    return r;
}

uint8_t ALU::xra(Registers& reg, uint8_t value) {
    uint8_t r = reg.A ^ value;

    uint8_t newF = 0;
    if (r & 0x80)             newF |= F_S;
    if (r == 0)               newF |= F_Z;
    if (parity<uint8_t>(r))     newF |= F_P;
    // always clears AC and C

    reg.A = r;
    reg.Flags = (reg.Flags & ~MASK_SZPAC) | newF;
    return r;
}

uint8_t ALU::daa(Registers& reg) {
    bool carry = false;
    uint8_t before = reg.A;

    if ((before & 0x0F) > 9 || (reg.Flags & F_AC)) {
        before += 0x06;
        reg.Flags |= F_AC;
    }
    else {
        reg.Flags &= ~F_AC;
    }

    if ((before >> 4) > 9 || (reg.Flags & F_C)) {
        before += 0x60;
        carry = true;
    }

    reg.A = before;
    if (carry) reg.Flags |= F_C; else reg.Flags &= ~F_C;

    updateFlags<uint8_t>(reg, reg.A, MASK_SZP);
    return reg.A;
}

uint16_t ALU::dad(Registers& reg, RegisterPair& rp) {
    uint32_t sum = uint32_t(reg.HL.get()) + rp.get();

    if (sum > 0xFFFF) reg.Flags |= F_C;
    else              reg.Flags &= ~F_C;

    reg.HL.set(uint16_t(sum));
    return reg.HL.get();
}

