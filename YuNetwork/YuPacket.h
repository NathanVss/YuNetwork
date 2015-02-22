#pragma once

#include "MultiContainer.h"
#include "StringStream.h"

namespace YuNetwork {

class YuPacket
{
public:
	YuPacket(void) {
		YuPacket::packetsTotal++;
	};
	~YuPacket(void) {
	};

	void loadStream(std::string str) {

		stringStream.setStream(str);

	}
	void loadToStream() {
		stringStream.add(packetId);
		stringStream.add(publicId);
		stringStream.add(clientId);
	}
	void readFromStream() {
		packetId = stringStream.readInt();
		publicId = stringStream.readInt();
		clientId = stringStream.readString();
	}
	std::string& getStream() {
		return stringStream.getStream();
	}
	
	int packetId;
	std::string clientId;
	int publicId;

	static int packetsTotal;

	static const int yuPacketId = 1;
	static const int yuStringPacketId = 2;
	static const int yuAuthPacketId = 3;

protected:
	StringStream stringStream;
};


class YuAuthPacket : public YuPacket {
public:
	bool success;

	YuAuthPacket() : YuPacket() {
		success = false;
		packetId = YuPacket::yuAuthPacketId;


	};
	~YuAuthPacket() {

	};
	void loadToStream() {
		YuPacket::loadToStream();

		stringStream.add(success);
	}
	void readFromStream() {
		YuPacket::readFromStream();
		success = stringStream.readBool();
	}


};
//
//class YuStringPacket : public YuPacket {
//
//public:
//	std::string message;
//
//	YuStringPacket() : YuPacket() {
//		container.addStringVar(std::string("message"));
//		packetId = yuStringPacketId;
//	};
//	~YuStringPacket() {
//
//	};
//
//	virtual void loadToContainer() {
//		YuPacket::loadToContainer();
//		container.setStringVar(std::string("message"), message);
//	};
//	virtual void loadFromContainer() {
//		YuPacket::loadFromContainer();
//		message = container.getStringVar(std::string("message"));
//	};
//
//
//};

}