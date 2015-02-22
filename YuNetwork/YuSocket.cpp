#include "YuSocket.h"
#include <iostream>

namespace YuNetwork {

YuSocket::YuSocket() : Object()
{
}

YuSocket::YuSocket(TCPsocket _socket) : Object(){

	socket = _socket;

}


YuSocket::YuSocket(Container* c, std::string _serverAdress, int _port) : Object(c){
	serverAddress = _serverAdress;
	port = _port;
}

YuSocket::~YuSocket(void){
	//SDLNet_TCP_Close(socket);
}

void YuSocket::copyToBuffer(std::string& msg) {

	strcpy(buffer, msg.c_str());

}


SDLNet_SocketSet* YuSocket::getSocketSet() {
	return &socketSet;
}


char* YuSocket::getBuffer() {
	return buffer;
}

bool YuSocket::tryToConnect(int setSize) {
	socketSet = SDLNet_AllocSocketSet(setSize);


	int hostResolved;
	if(serverAddress.empty()) {
		hostResolved = SDLNet_ResolveHost(&serverIp,NULL, port);

	} else {
		hostResolved = SDLNet_ResolveHost(&serverIp,serverAddress.c_str(), port);

	}

	if(hostResolved == -1) {
		std::cout << "Failed to resolve host : " << SDLNet_GetError() << std::endl;
		return false;

	} else {


		std::cout << "Successfully resolved server host to IP : " << serverAddress << std::endl;
	}

	socket = SDLNet_TCP_Open(&serverIp);

	if(!socket) {
		std::cout << "Failed to open the server socket " << SDLNet_GetError() << std::endl;
		return false;
	} else {

		std::cout << "Successfully created the socket server" << std::endl;
	}

	SDLNet_TCP_AddSocket(socketSet, socket);	
	return true;
}


}