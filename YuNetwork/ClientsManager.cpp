#include "ClientsManager.h"
#include "YuClient.h"
#include <iostream>
#include "Container.h"
#include <time.h>

namespace YuNetwork {


ClientsManager::ClientsManager() {


};

ClientsManager::ClientsManager(Container* c) : Object(c){
	bufferIds = 0;
}


ClientsManager::~ClientsManager(void)
{
}

std::vector<YuClient*>& ClientsManager::getClients() {
	return clients;
}


int ClientsManager::getClientsNumber() {
	return clients.size();
}

YuClient* ClientsManager::newClient(YuSocket socket) {
	YuClient* client = new YuClient(socket, 60*60);
	client->setPublicId(getNewId());
	client->setClientId(randomString(16));
	addClient(client);
	return client;

}

int ClientsManager::getNewId() {
	bufferIds++;
	return bufferIds;
}

void ClientsManager::addClient(YuClient* client) {
	clients.push_back(client);
};
void ClientsManager::update() {
	std::vector<YuClient*> temp;

	for(int i = 0; i < clients.size(); i++) {

		clients[i]->update();
		if(!clients[i]->isLost()) {
			temp.push_back(clients[i]);
		} else {
			//container->getYuHostSocket()->deleteSocket(clients[i]);
			delete clients[i];
			std::cout << "Just lost client " << i << std::endl;
		}

	}
	clients = temp;
};

YuClient* ClientsManager::getClient(int i) {
	return clients[i];
}

std::string ClientsManager::randomString(int len) {
	srand(time(0));
	std::string str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	int pos;
	while(str.size() != len) {
	pos = ((rand() % (str.size() - 1)));
	str.erase (pos, 1);
	}
	return str;
}

}