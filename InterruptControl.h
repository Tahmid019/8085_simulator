#pragma once
#include "Head_1.h"

class InterruptControl {
private:
    uint8_t mask;

public:
    InterruptControl();

    void setMask(uint8_t value);
    uint8_t readMask() const;
};
