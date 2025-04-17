#pragma once
#include "Head_1.h"

class IO {
private:
	string portName;
	bool isConnected;
public:
	IO();
	~IO();

	bool connect();
	void disconnect();
	uint8_t read(uint8_t portAddress);
	void write(uint8_t portAddress, uint8_t value);

	bool isPortConnected() const;
};


