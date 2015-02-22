#pragma once
#include <YuNetwork\YuPacket.h>


class PacketIds {
public:
	static const int packetMoveId = 100;
	static const int packetPositionId = 101;
	static const int packetPlayerId = 102;
};
//
class PlayerPacket : public YuNetwork::YuPacket {
public:
	float x;
	float y;
	int moveId;
	PlayerPacket() {
		YuPacket::YuPacket();
		packetId = PacketIds::packetPlayerId;
	};
	~PlayerPacket() {

	};

	void loadToStream() {
		YuPacket::loadToStream();
		stringStream.add(x);
		stringStream.add(y);
	}
	void readFromStream() {
		YuPacket::readFromStream();
		x = stringStream.readFloat();
		y = stringStream.readFloat();
	}

};

class PacketMove : public YuNetwork::YuPacket
{
public:
	float velocityX;
	float velocityY;
	int id;


	PacketMove(void) {
		YuPacket::YuPacket();
		packetId = PacketIds::packetMoveId;
	};
	~PacketMove(void) {
	};



	void loadToStream() {
		YuPacket::loadToStream();
		stringStream.add(id);
		stringStream.add(velocityX);
		stringStream.add(velocityY);
	}
	void readFromStream() {
		YuPacket::readFromStream();
		id = stringStream.readInt();
		velocityX = stringStream.readFloat();
		velocityY = stringStream.readFloat();
	}
};

