#pragma once

#include "Object.h"
#include "YuSocket.h"
#include <vector>

namespace YuNetwork {
	
class YuClient;


class ServerHandler : public Object
{
private:
	YuSocket serverSocket;
	int maxClients;

public:
	ServerHandler(void);
	ServerHandler(Container* c, int port);
	~ServerHandler(void);
	void update();

	YuClient* handleNewClient();
	bool newClientWaiting();

	bool isReady(YuClient* client);
	std::vector<std::string> receiveFrom(YuClient* client);
	void send(YuClient* client, std::string &message);
	void sendPacketStream(YuClient* client);
	void sendTickPacketStream(YuClient* client);

};


}