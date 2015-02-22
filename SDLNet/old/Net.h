#pragma once

#include <iostream>
#include <dependencies\SDL2-2.0.3\include\SDL.h>
#include <dependencies\SDL2-2.0.3\include\SDL_net.h>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef char charbuf[256];

class NIpAdress {
private:
	IPaddress ip;

public:
	NIpAdress();
	NIpAdress(Uint16 port);
	NIpAdress(std::string host, Uint16 port);
	void setIp(IPaddress sdlIp);
	bool ok() const;
	IPaddress getIpAdress() const;
	Uint32 getHost() const;
	Uint16 getPort() const;

};

class NetMessage {
public:
	NetMessage();
	~NetMessage();
	virtual int numToLoad();
	virtual int numtoUnload();

	void loadBytes(charbuf& inputBuffer, int n);
	void unloadBytes(charbuf& destBuffer);
	void finish();

protected:
	charbuf buffer;
	enum bufStates {
		EMPTY,
		READING,
		WRITING,
		FULL
	};

	bufStates state;
	void reset();

};

class Net
{
public:
	Net(void);
	~Net(void);
	bool init();
	void quit();

};

