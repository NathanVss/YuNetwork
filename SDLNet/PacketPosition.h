#pragma once

#include <YuNetwork\YuPacket.h>

class PacketIds {
public:
	static const int packetPositionId = 100;
};

class PacketMove : public YuNetwork::YuPacket
{
public:
	float velocityX;
	float velocityY;
	int id;


	PacketMove(void) {
		YuPacket::YuPacket();
		packetId = PacketIds::packetPositionId;

		container.addFloatVar("velocityX");
		container.addFloatVar("velocityY");
		container.addIntVar("id");
	};
	~PacketMove(void) {
	};

	virtual void loadToContainer() {
		YuPacket::loadToContainer();
		container.setVar("velocityX", velocityX);
		container.setVar("velocityY", velocityY);
		container.setVar("id", id);
	}
	virtual void loadFromContainer() {
		YuPacket::loadFromContainer();
		velocityX = container.getFloatVar("velocityX");
		velocityY = container.getFloatVar("velocityY");
		id = container.getIntVar("id");
	}
};

