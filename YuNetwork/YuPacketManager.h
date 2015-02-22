#pragma once

#include <vector>
#include <string>
#include "Object.h"

namespace YuNetwork {

class YuClientSocket;
class YuHostSocket;
class YuClient;

class YuPacket;


class YuPacketManager : public Object
{
private:
	std::string bufferStream;
	std::string tickBufferStream;
	std::vector<std::string> packetBuffer;
	std::vector<std::string> tickPacketBuffer;

public:
	YuPacketManager(void);
	YuPacketManager(Container* c);
	~YuPacketManager(void);

	void addToTickBuffer(std::string &str) {
		tickPacketBuffer.push_back(str);
	}
	void resetTickBuffer() {
		tickPacketBuffer.clear();
	}
	std::string& getBufferStream() {
		return bufferStream;
	}
	std::string& getTickBufferStream() {
		return tickBufferStream;
	}
	bool isPacketBufferEmpty() {
		return bufferStream.empty();
	}
	bool isTickPacketBufferEmpty() {
		return tickBufferStream.empty();
	}

	void addToBuffer(std::string &str) {
		packetBuffer.push_back(str);
	}
	void resetBuffer() {
		packetBuffer.clear();
	}
	std::vector<std::string>& getPacketBuffer() {
		return packetBuffer;
	}


	void buildBufferStream();
	void buildTicksBufferStream();

	//void sendBuffer(YuClientSocket& socket, bool debug = false);
	//void sendBuffer(YuHostSocket& hostSocket, YuClient& client);
	//void sendTickBuffer(YuHostSocket& hostSocket, bool debug = false);

	std::string convertToString(YuPacket *yuPacket);

	std::string convertToString(std::vector<YuPacket> yuPackets);
	int getPacketId(std::string &message);
	int getPacketsNumber(std::string &message);
	std::string getPacketString(int i, std::string &totalMessage);
	std::vector<int> getPacketsIds(std::string &message);
	void transfertToPacket(YuPacket &yuPacket, std::string &message);
	void transfertToPacket(YuPacket &yuPacket, std::string &totalMessage, int i);


	void replaceAll(std::string& str, const std::string& from, const std::string& to);
};


}