#pragma once
#include "Head_1.h"
#include "Memory.h"

/*

	FLAG: Sgn - Z - P - AC C

*/

struct RegisterPair {
	uint8_t low, high;
	
	uint16_t get() {
		return (high << 8) | low;
	}

	void set(uint16_t value) {
		low = value & 0x00FF;
		high = (value >> 8) & 0x00FF;
	}
};


class StackPointer {
private:
    uint16_t spValue;

public:
    StackPointer() : spValue(0) {}

    uint16_t get() const {
        return spValue;
    }

    void set(uint16_t value) {
        spValue = value;
    }

    uint8_t pop(Memory& memory) {
        uint8_t value = memory.read(spValue); 
        spValue++;                            
        return value;                         
    }

	uint8_t push(Memory& memory, uint8_t value) {
		spValue--;
		memory.write(spValue, value);
		return value;
	}

    StackPointer& operator=(uint16_t value) {
        spValue = value;
        return *this;    
    }

    StackPointer& operator--() {
        --spValue;
        return *this;
    }

    StackPointer& operator--(int) {
		StackPointer temp = *this;
        --spValue;
        return temp;
    }

    StackPointer& operator++() {
        ++spValue;
        return *this;
    }

    StackPointer& operator++(int) {
		StackPointer temp = *this;
        ++spValue;
        return temp;
    }

    operator uint16_t() const {
        return spValue;
    }
};


class Registers {
public:
    uint8_t A, B, C, D, E, H, L;
    uint16_t PC;
    uint8_t Flags;
    bool interruptEnabled = false;

    RegisterPair BC = { B, C };
    RegisterPair DE = { D, E };
    RegisterPair HL = { H, L };

    StackPointer SP; 

    Registers() = default;
};

