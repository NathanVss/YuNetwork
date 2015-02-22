#pragma once

#include <iostream>
#include <dependencies\SDL2-2.0.3\include\SDL.h>
#include <dependencies\SDL2-2.0.3\include\SDL_net.h>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

class NTcpSocket
{
public:
	NTcpSocket(void);
	virtual ~NTcpSocket();
	virtual void setSocket(TCPsocket _socket);
	bool ok() const;
	bool ready() const;
	virtual void onReady();

protected:
	TCPsocket socket;
	SDLNet_SocketSet set;


};

