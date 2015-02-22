#pragma once

namespace YuNetwork {

class ClientsManager;
class YuHostSocket;
class YuPacketManager;
class YuClientSocket;
class ClientHandler;

class Container
{
public:
	Container(void) {

	};
	~Container(void) {

	};

	void setClientsManager(ClientsManager* c) {
		clientsManager = c;
	};
	ClientsManager* getClientsManager() {
		return clientsManager;

	}

	void setYuHostSocket(YuHostSocket* y) {
		yuHostSocket = y;
	}
	YuHostSocket* getYuHostSocket() {
		return yuHostSocket;
	}

	void setYuPacketManager(YuPacketManager* y) {
		yuPacketManager = y;
	}
	YuPacketManager* getYuPacketManager() {
		return yuPacketManager;
	}

	void setYuClientSocket(YuClientSocket* c) {
		yuClientSocket = c;
	}
	YuClientSocket* getYuClientSocket() {
		return yuClientSocket;
	}
	void setClientHandler(ClientHandler* c) {
		clientHandler = c;
	}
	ClientHandler* getClientHandler() {
		return clientHandler;
	}

private:
	ClientHandler* clientHandler;
	ClientsManager* clientsManager;
	YuHostSocket* yuHostSocket;
	YuPacketManager* yuPacketManager;
	YuClientSocket* yuClientSocket;

};

}