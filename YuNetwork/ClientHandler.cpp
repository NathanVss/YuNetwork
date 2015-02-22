#include "ClientHandler.h"
#include "YuPacketManager.h"
#include "YuClient.h"
#include "YuSocket.h"
#include <iostream>
namespace YuNetwork {

ClientHandler::ClientHandler(void){
}


ClientHandler::ClientHandler(Container* c) : Object(c){
	YuSocket socket(container, "192.168.1.10", 1234);

	client = YuClient(socket, 60*60);
}

ClientHandler::~ClientHandler(void){
	SDLNet_TCP_Close(*client.getSocket()->getSocket());
}


YuClient* ClientHandler::getClient() {
	return &client;
}


bool ClientHandler::send(std::string &msg) {

	YuSocket* socket = client.getSocket();
	socket->copyToBuffer(msg);
	int length = msg.size() + 1;	

	if(SDLNet_TCP_Send(*(socket->getSocket()), (void*)socket->getBuffer(), length) < length) {
		return false;
	}
	//std::cout << "SENT : " << msg << std::endl;
	return true;

}
bool ClientHandler::isReady() {
	
	YuSocket* socket = client.getSocket();
	int socketActive = SDLNet_CheckSockets(*(socket->getSocketSet()), 0);

	if(socketActive != 0) {

		int socketReady = SDLNet_SocketReady(*(socket->getSocket()));
		if(socketReady != 0) {
			return true;
		}

	}
	
	return false;



}

std::vector<std::string> ClientHandler::receive() {
	std::vector<std::string> stringBuffer;
	YuSocket* socket = client.getSocket();
		
	int byteCount = SDLNet_TCP_Recv(*socket->getSocket(), socket->getBuffer(), YuSocket::bufferSize);

	if(byteCount > 0) {

		char* buffer = socket->getBuffer();

		std::string curString;
		for(int i = 0; i < byteCount; i++) {

			if(buffer[i] != '\0') {

				curString.push_back(buffer[i]);
			} else {
				stringBuffer.push_back(curString);
				curString.clear();
			}

		}
		//std::cout << std::endl << "NEW READING : " << std::endl;
		//for(int i = 0; i < stringBuffer.size(); i++) {

		//	std::cout << stringBuffer[i] << std::endl;
		//}
		//std::cout << std::endl;

		client.newLifeSign();


	}
	return stringBuffer;

}
void ClientHandler::update() {

	if(!client.isConnected()) {
		bool connected = client.getSocket()->tryToConnect(1);
		client.setConnected(connected);
		
		if(connected) {
			//send(std::string("tick"));
		}
	}

}

void ClientHandler::sendPacketStream() {
	if(!container->getYuPacketManager()->isPacketBufferEmpty()) {

		send(container->getYuPacketManager()->getBufferStream());
	}
}


}