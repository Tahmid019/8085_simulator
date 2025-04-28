#pragma once
#include "IODevice.h"

class IO : public IODevice {
public:
    IO(const string& name = "New Port");
    ~IO();

    bool connect() override;
    void disconnect() override;
    uint8_t read(uint8_t portAddress) override;
    void write(uint8_t portAddress, uint8_t value) override;
};
