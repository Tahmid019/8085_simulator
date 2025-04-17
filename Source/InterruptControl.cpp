#include "../Headers/InterruptControl.h"

InterruptControl::InterruptControl() : mask(0) {}

void InterruptControl::setMask(uint8_t value) {
    mask = value;
}

uint8_t InterruptControl::readMask() const {
    return mask;
}