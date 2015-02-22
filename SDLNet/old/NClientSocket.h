#pragma once

#include <iostream>
#include <dependencies\SDL2-2.0.3\include\SDL.h>
#include <dependencies\SDL2-2.0.3\include\SDL_net.h>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "NTcpSocket.h"

#include "Net.h"
#include "HostSocket.h"

class NClientSocket : public NTcpSocket
{
private:
	NIpAdress remoteIp;

public:
	NClientSocket(void);
	NClientSocket(std::string &host, Uint16 port);
	~NClientSocket(void);
	bool connect(NIpAdress& remoteIp);
	bool connect(CHostSocket& listenerSocket_);
	void setSocket(TCPsocket socket_);
	NIpAdress getIpAdress() const;
	virtual void onReady();
	bool receive(NetMessage& rData);
	bool send(NetMessage& sData);
};

