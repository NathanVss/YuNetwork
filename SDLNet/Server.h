#pragma once

#include "Object.h"
#include <YuNetwork\YuClient.h>
#include <YuNetwork\ServerHandler.h>


class PlayersManager;

class Server : public Object
{
private:
	YuNetwork::YuHostSocket* hostSocket;
	PlayersManager* playersManager;
	YuNetwork::ServerHandler* serverHandler;
public:
	Server(void);
	~Server(void);

	void loop();

	void handleNewClients();
	void handleTickBuffer();
	void updateClients();
	void handlePacket(std::string &stream, int packetId, YuNetwork::YuClient* client);
};

