#include "../Headers/IO.h"

IO::IO() : portName("New Port"), isConnected(false) {}

IO::~IO() { disconnect(); }

bool IO::connect() {
	isConnected = true;
	cout << "Connected to Port: " << portName << endl;
	return isConnected;
}

void IO::disconnect() {
	if (isConnected) {
		isConnected = false;
		cout << "Disconnect from port: " << portName << endl;
	}
}

uint8_t IO::read(uint8_t portAddress) {
	if (!isConnected) {
		throw runtime_error("Port not connected. Cannot Read Data from port: " + portName);
	}

	cout << "Reading Dta from port Address: " << static_cast<int>(portAddress) << endl;
	return 0xFF;
}

void IO::write(uint8_t portAddress, uint8_t value) {
	if (!isConnected) {
		throw runtime_error("Port Not Connected. Cannot Write data to port: " + portName + " at address: " + to_string(portAddress) + " with value: " + to_string(value));
	}

	cout << "Writing Data : port Address: { " << static_cast<int>(portAddress) << " } with value: [ " << static_cast<int>(value) << " ]" << endl;
}

bool IO::isPortConnected() const {
	return isConnected;
}