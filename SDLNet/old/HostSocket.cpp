#include "HostSocket.h"
#include "NClientSocket.h"


CHostSocket::CHostSocket(NIpAdress& ipAdress_){
	NTcpSocket::NTcpSocket();
	IPaddress ipH = ipAdress_.getIpAdress();
	if(!(socket = SDLNet_TCP_Open(&ipH))) {

		SDLNet_FreeSocketSet(set);
		std::cout << "SDLNet TCP Open :" << SDLNet_GetError() << std::endl;


	}
}

CHostSocket::CHostSocket(Uint16 port) {

	NIpAdress ipListener(port);
	if(!ipListener.ok()) {
		socket = NULL;
	} else {

		NTcpSocket::NTcpSocket();
		IPaddress ipH = ipListener.getIpAdress();
		if(!(socket = SDLNet_TCP_Open(&ipH))) {

			SDLNet_FreeSocketSet(set);
			std::cout << "SDLNet _TCP Open : " << SDLNet_GetError() << std::endl;

		}

	}

}


CHostSocket::~CHostSocket(void)
{
}

bool CHostSocket::accept(NClientSocket& clientSocket_) {
	TCPsocket cs;
	if((cs = SDLNet_TCP_Accept(socket))) {

		clientSocket_.setSocket(cs);
		return true;

	}
	return false;

}

void CHostSocket::onReady() {


}