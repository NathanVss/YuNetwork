#include "Net.h"


Net::Net(void){

}


Net::~Net(void)
{
}


bool Net::init() {

	if(SDLNet_Init() < 0) {
		std::cout << "SDLNet init error : " << SDLNet_GetError() << std::endl;
		return false;
	} else {
		return true;
	}
}

void Net::quit() {
	SDLNet_Quit();
}

NetMessage::NetMessage() {
	reset();
}

NetMessage::~NetMessage() {

}

void NetMessage::reset() {

	for(int i = 0; i < 256; i++) {

		buffer[i] = 0;
	}
	state = EMPTY;
}

void NetMessage::finish() {

	if(state == READING) {
		state = FULL;
	}
}

int NetMessage::numToLoad() {

	if(state == EMPTY) {
		return 255;
	}
	return 0;
}

int NetMessage::numtoUnload() {

	if(state == FULL) {
		return strlen(buffer) + 1;
	}
	return 0;
}

void NetMessage::loadBytes(charbuf& inputBuffer, int n) {
	for(int i = 0; i < n; i++) {
		buffer[i] = inputBuffer[i];
	}
	state = READING;
}


void NetMessage::unloadBytes(charbuf& destBuffer) {


	for(int i = 0; i < numtoUnload(); i++) {

		destBuffer[i] = buffer[i];
	}
	reset();
}








NIpAdress::NIpAdress(Uint16 port) {

	if(SDLNet_ResolveHost(&ip, NULL, port) < 0) {

		std::cout << "SDLNet Resolve host : " << SDLNet_GetError() << std::endl;
		ip.host = 0;
		ip.port = 0;

	}

};

NIpAdress::NIpAdress(std::string host, Uint16 port) {

	if(SDLNet_ResolveHost(&ip, host.c_str(), port) < 0) {
		std::cout << "SDLNet Resolve host : " << SDLNet_GetError() << std::endl;
		ip.host = 0;
		ip.port = 0;

	}

};

NIpAdress::NIpAdress() {
	ip.host = 0;
	ip.port = 0;
}

bool NIpAdress::ok() const {
	return !(ip.port == 0);
}

void NIpAdress::setIp(IPaddress sdlIp) {
	ip = sdlIp;
}

IPaddress NIpAdress::getIpAdress() const {
	return ip;
}

Uint32 NIpAdress::getHost() const {
	return ip.host;
}

Uint16 NIpAdress::getPort() const {
	return ip.port;
}