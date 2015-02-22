#include "NClientSocket.h"


NClientSocket::NClientSocket(void){
	NTcpSocket::NTcpSocket();
}

NClientSocket::NClientSocket(std::string &host, Uint16 port) {

	NIpAdress remoteIp(host.c_str(), port);
	if(!remoteIp.ok()) {
		socket = NULL;
	} else {
		NTcpSocket::NTcpSocket();
		connect(remoteIp);
	}
}


NClientSocket::~NClientSocket(void)
{
}

bool NClientSocket::connect(CHostSocket& listenerSocket) {

	return false;
}

bool NClientSocket::connect(NIpAdress& remoteIp) {
	TCPsocket cs;
	IPaddress ip = remoteIp.getIpAdress();

	if((cs = SDLNet_TCP_Open(&ip))) {

		setSocket(cs);
		return true;
	} else {
		std::cout << "SDLNet TCP Open : " << SDLNet_GetError() << std::endl;
		return false;
	}
}

void NClientSocket::setSocket(TCPsocket sdlSocket_) {

	NTcpSocket::setSocket(sdlSocket_);
	IPaddress* ips;
	if((ips = SDLNet_TCP_GetPeerAddress(socket))) {

		remoteIp.setIp(*ips);
		Uint32 hbo = remoteIp.getHost();
		Uint16 pbo = remoteIp.getPort();
		std::cout << "Client Connected : " << SDLNet_Read32(&hbo) << " " << SDLNet_Read16(&pbo) << std::endl;

	} else {
		std::cout << "SDL Net TCP GetPeer Address : " << SDLNet_GetError() << std::endl;
	}

}

NIpAdress NClientSocket::getIpAdress() const {

	return remoteIp;

}

bool NClientSocket::receive(NetMessage& rData) {

	if(socket == NULL) {
		return false;
	}

	charbuf buf;

	while(rData.numToLoad() > 0) {

		if(SDLNet_TCP_Recv(socket, buf, rData.numToLoad()) > 0) {
			rData.loadBytes(buf, rData.numToLoad());
		} else {
			return false;
		}

	}
	rData.finish();
	return true;

}

bool NClientSocket::send(NetMessage& sData) {


	if(socket == NULL) {
		return false;
	}

	charbuf buf;
	int len;

	while((len = sData.numtoUnload()) > 0) {

		sData.unloadBytes(buf);

		if(SDLNet_TCP_Send(socket, (void*)buf, len) < len) {

			std::cout << "SDLNet TCP Send : " << SDLNet_GetError() << std::endl;
			return false;

		}
		
	}

	std::cout << "SENT : " << buf << std::endl;
	return true;

}


void NClientSocket::onReady() {


}
