#pragma once

#include "Object.h"
#include <string>

class ControllerClientPlayer;

class ControllerClientPackets : public Object
{
public:
	ControllerClientPackets(void);
	ControllerClientPackets(MyContainer* c);
	~ControllerClientPackets(void);

	void update();
	void handlePacket(std::string &stream, int packetId);

	void attachControllerPlayer(ControllerClientPlayer* c) {
		controllerPlayer = c;
	}

private:
	ControllerClientPlayer* controllerPlayer;
};

