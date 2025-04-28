#include "../Headers/IODevice.h"

IODevice::IODevice(const string& name) : portName(name), isConnected(false) {}

IODevice::~IODevice() {}

bool IODevice::isPortConnected() const {
    return isConnected;
}
