#pragma once

#include "YuClient.h"
#include "Object.h"
#include <vector>
#include <string>

namespace YuNetwork {

class ClientHandler : public Object
{
private:
	YuClient client;



public:
	ClientHandler(void);
	ClientHandler(Container* c);
	~ClientHandler(void);

	bool send(std::string& msg);
	bool isReady();
	std::vector<std::string> receive();
	void update();
	YuClient* getClient();
	void sendPacketStream();

};

}