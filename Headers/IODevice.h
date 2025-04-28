#pragma once
#include "Head_1.h"

class IODevice {
protected:
    string portName;
    bool isConnected;

public:
    IODevice(const string& name = "Unnamed Port");
    virtual ~IODevice();

    virtual bool connect() = 0;
    virtual void disconnect() = 0;
    virtual uint8_t read(uint8_t portAddress) = 0;
    virtual void write(uint8_t portAddress, uint8_t value) = 0;

    bool isPortConnected() const;
};
