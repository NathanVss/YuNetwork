#pragma once

#include "Object.h"
#include <vector>
#include "YuSocket.h"

namespace YuNetwork {

class YuClient;

class ClientsManager : public Object
{
public:
	ClientsManager();
	ClientsManager(Container* c);
	~ClientsManager(void);

	YuClient* newClient(YuSocket socket);
	void addClient(YuClient* client);
	YuClient* getClient(int i);
	std::vector<YuClient*>& getClients();

	int getClientsNumber();
	void update();
	int getNewId();
	std::string randomString(int len);


private:
	std::vector<YuClient*> clients;
	int bufferIds;
};


}