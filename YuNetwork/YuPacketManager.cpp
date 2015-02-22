#include "YuPacketManager.h"
#include "YuPacket.h"
#include <string>
#include <algorithm>
#include "YuClient.h"
#include "ClientsManager.h"

namespace YuNetwork {

YuPacketManager::YuPacketManager(void)
{
}

YuPacketManager::YuPacketManager(Container* c) : Object(c) {

}


YuPacketManager::~YuPacketManager(void)
{
}

void YuPacketManager::buildBufferStream() {
	bufferStream.clear();
	for(int i = 0; i < packetBuffer.size(); i++) {
		bufferStream += packetBuffer[i] + '|';
	}

}
void YuPacketManager::buildTicksBufferStream() {
	tickBufferStream.clear();
	for(int i = 0; i < tickPacketBuffer.size(); i++) {
		tickBufferStream += tickPacketBuffer[i] + '|';
	}

}

int YuPacketManager::getPacketId(std::string &message) {

	std::string id;
	for(int i = 1; i < message.size(); i++) {
		if(message[i] == ';') {
			break;
		} else {
			id += message[i];
		}
	}
	int iid = -1;
	try {
		iid = std::stoi(id);
		
	} catch(std::invalid_argument& e) {
		// NOT A NUMBER
	}

	return iid;

}


std::string YuPacketManager::getPacketString(int j, std::string &totalMessage) {

	std::string message;
	int curPos = 0;
	bool in = false;
	for(int i = 0; i < totalMessage.size(); i++) {

		if(curPos == j) {

			if(totalMessage[i] == '|') {
				break;
			}
			message.push_back(totalMessage[i]);


		} else {

			if(totalMessage[i] == '|') {
				curPos++;
			}
		}


	}
	return message;

}

std::vector<int> YuPacketManager::getPacketsIds(std::string &message) {

	std::vector<int> ids;

	int packetsNumber = getPacketsNumber(message);
	for(int i = 0; i < packetsNumber; i++) {


		std::string curPacket = getPacketString(i, message);
		int id = getPacketId(curPacket);
		ids.push_back(id);

	}

	return ids;
}


int YuPacketManager::getPacketsNumber(std::string &message) {

	int count = 0;
	for(int i = 0; i < message.size(); i++) {

		if(message[i] == '|') {
			count++;
		}

	}
	return count;

}

std::string YuPacketManager::convertToString(std::vector<YuPacket> yuPackets) {

	std::string message;
	for(int i = 0; i < yuPackets.size() ; i++) {
		message += yuPackets[i].getStream();
		message += '|';

	}
	return message;

}

void YuPacketManager::replaceAll(std::string& str, const std::string& from, const std::string& to) {
	if(from.empty())
		return;
	size_t start_pos = 0;
	while((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
}


}