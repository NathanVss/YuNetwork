#include "NTcpSocket.h"


NTcpSocket::NTcpSocket(void){
	socket = NULL;
	set = SDLNet_AllocSocketSet(10);
}


NTcpSocket::~NTcpSocket(void){
	if(socket != NULL) {

		SDLNet_TCP_DelSocket(set, socket);
		SDLNet_FreeSocketSet(set);
		SDLNet_TCP_Close(socket);

	}
}


void NTcpSocket::setSocket(TCPsocket socket_) {

	if(socket != NULL) {

		SDLNet_TCP_DelSocket(set, socket);
		SDLNet_TCP_Close(socket);

	}

	socket = socket_;

	if(SDLNet_TCP_AddSocket(set, socket) == -1) {

		std::cout << "SDLNet TCP AddSocket : " << SDLNet_GetError() << std::endl;
		socket = NULL;
	}

}

bool NTcpSocket::ok() const {

	return !(socket == NULL);
}

bool NTcpSocket::ready() const {

	bool rd = false;
	int numReady = SDLNet_CheckSockets(set, 0);

	if(numReady == -1) {
		std::cout << "SDLNet CheckSockets : " << SDLNet_GetError() << std::endl;

	} else {
		if(numReady) {
			rd = (bool)SDLNet_SocketReady(socket);
		}
	}
	return rd;
}

void NTcpSocket::onReady() {


}