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

class NClientSocket;

class CHostSocket : public NTcpSocket
{
public:
	CHostSocket(NIpAdress& ipAdress_);
	CHostSocket(Uint16 port);
	bool accept(NClientSocket&);
	virtual void onReady();
	~CHostSocket(void);
};

