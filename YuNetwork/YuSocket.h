#pragma once

#include "Object.h"
#include <string>
#include <dependecies\SDL2-2.0.3\include\SDL_net.h>

namespace YuNetwork {

class Container;

class YuSocket : public Object
{
public:
	YuSocket(void);
	YuSocket(TCPsocket);
	YuSocket(Container*, std::string _serverAdress, int port);
	~YuSocket(void);

	void copyToBuffer(std::string& msg);
	SDLNet_SocketSet* getSocketSet();
	char* getBuffer();
	bool tryToConnect(int setSize);
	TCPsocket* getSocket() {
		return &socket;
	}

	static const int bufferSize = 65536;

protected:
	TCPsocket socket;
	int port;
	IPaddress serverIp;
	SDLNet_SocketSet socketSet;
	std::string serverAddress;

	char buffer[bufferSize];
};



}