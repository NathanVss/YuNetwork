#include "ServerHandler.h"
#include "YuPacketManager.h"
#include "YuSocket.h"
#include "ClientsManager.h"
#include <iostream>
#include "YuClient.h"
namespace YuNetwork {

ServerHandler::ServerHandler(void)
{
}

ServerHandler::ServerHandler(Container* c, int port) : Object(c) {
	maxClients = 30;
	serverSocket = YuSocket(container, "", port);
	serverSocket.tryToConnect(maxClients);
}



ServerHandler::~ServerHandler(void)
{
}

YuClient* ServerHandler::handleNewClient() {

	TCPsocket newClientS = SDLNet_TCP_Accept(*serverSocket.getSocket());
	YuSocket socket(newClientS);
	SDLNet_TCP_AddSocket(*serverSocket.getSocketSet(), newClientS);

	YuClient* newClient = container->getClientsManager()->newClient(socket);
	return newClient;

}



bool ServerHandler::newClientWaiting() {


	// A mettre absolument car doit faire un update
	int numActiveSockets = SDLNet_CheckSockets(*serverSocket.getSocketSet(), 0);



	int activity = SDLNet_SocketReady(*serverSocket.getSocket());
	if(activity != 0) {
		
		if(container->getClientsManager()->getClientsNumber() < maxClients) {
			return true;
		}

	}

	return false;
}


void ServerHandler::update() {



}

bool ServerHandler::isReady(YuClient* client) {

	TCPsocket d = *client->getSocket()->getSocket();
	int clientSocketActivity = SDLNet_SocketReady(*(client->getSocket()->getSocket()));
	if(clientSocketActivity != 0 && !client->isLost()) {
	//if(clientSocketActivity != 0) {
		return true;
	}
	return false;
}
std::vector<std::string> ServerHandler::receiveFrom(YuClient* client) {

	YuSocket* socket = client->getSocket();
	char* buffer = socket->getBuffer();
	int receivedBytes = SDLNet_TCP_Recv(*socket->getSocket(), buffer, YuSocket::bufferSize);

	std::vector<std::string> stringBuffer;

	if(receivedBytes > 0) {

		client->newLifeSign();

		std::string curString;
		for(int i = 0; i < receivedBytes; i++) {

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


		return stringBuffer;

	}
	return stringBuffer;
	
}
void ServerHandler::send(YuClient* client, std::string &message) {
	int length = message.size() + 1;

	client->getSocket()->copyToBuffer(message);
	

	if(!client->isLost() && SDLNet_TCP_Send(*client->getSocket()->getSocket(), (void*)client->getSocket()->getBuffer(), length) < length) {


	} else {
		//std::cout << "Sent : " << message << std::endl;
	}
}
void ServerHandler::sendPacketStream(YuClient* client) {
	if(!container->getYuPacketManager()->isPacketBufferEmpty()) {
		send(client, container->getYuPacketManager()->getBufferStream());
	}
}
void ServerHandler::sendTickPacketStream(YuClient* client) {
	if(!container->getYuPacketManager()->isTickPacketBufferEmpty()) {

		send(client, container->getYuPacketManager()->getTickBufferStream());

	}

}

}