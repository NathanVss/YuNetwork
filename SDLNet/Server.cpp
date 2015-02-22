#include "Server.h"
#include <iostream>
#include <dependecies\SDL2-2.0.3\include\SDL.h>
#include <dependecies\SDL2-2.0.3\include\SDL_net.h>
#include <vector>

#include <YuNetwork\YuPacket.h>
#include <YuNetwork\YuPacketManager.h>
#include <YuNetwork\ClientsManager.h>
#include <YuNetwork\YuClient.h>
#include <Noxel-OpenGL\YuEngine\FpsCounter.h>


#include "MainScene.h"
#include "MyContainer.h"
#include "Packets.h"
#include "PlayersManager.h"
#include "ControllerServerPlayer.h"

Server::Server(void){
	myContainer = new MyContainer();
	loop();
}


Server::~Server(void){
}

void Server::handleNewClients() {


	if(serverHandler->newClientWaiting()) {

		YuNetwork::YuClient* client = serverHandler->handleNewClient();
		//YuNetwork::YuClient* yuClient = hostSocket->handleNewClient();


		YuNetwork::YuAuthPacket authPacket;
		authPacket.success = true;
		authPacket.clientId = client->getClientId();
		authPacket.publicId = client->getPublicId();
		authPacket.loadToStream();
		myContainer->getYuPacketManager()->addToBuffer(authPacket.getStream());
		myContainer->getYuPacketManager()->buildBufferStream();
		serverHandler->sendPacketStream(client);
		//myContainer->getYuPacketManager()->sendBuffer(*hostSocket, *client);
		myContainer->getYuPacketManager()->resetBuffer();

		std::cout << "Welcome client " << client->getPublicId() << std::endl;


		Player* newPlayer = myContainer->getPlayersManager()->newPlayer();
		newPlayer->setPublicId(authPacket.publicId);
		newPlayer->setClientId(authPacket.clientId);
		newPlayer->setController(new ControllerServerPlayer(myContainer, newPlayer));
		
	}
}

void Server::updateClients() {

	for(int i = 0; i < myContainer->getClientsManager()->getClientsNumber(); i++) {
		YuNetwork::YuClient* yuClient = myContainer->getClientsManager()->getClient(i);

		if(serverHandler->isReady(yuClient)) {

			std::vector<std::string> receivedBuffer = serverHandler->receiveFrom(yuClient);

			for(int k = 0; k < receivedBuffer.size(); k++) {

				//std::cout << "Received : " << receivedBuffer[k] << std::endl;

				if(receivedBuffer[k] != "" && receivedBuffer[k] != "tick") {
					std::vector<int> packetIds = myContainer->getYuPacketManager()->getPacketsIds(receivedBuffer[k]);
					for(int i = 0; i < packetIds.size(); i++) {
						std::string curStream = myContainer->getYuPacketManager()->getPacketString(i, receivedBuffer[k]);


						handlePacket(curStream, packetIds[i], yuClient);
					}
				}
			}

		}

	}

}

void Server::handlePacket(std::string &stream, int packetId, YuNetwork::YuClient* client) {


	if(packetId == PacketIds::packetMoveId) {
						
		PacketMove packetMove;
		packetMove.loadStream(stream);
		packetMove.readFromStream();

		Player* player = myContainer->getPlayersManager()->getPlayer(packetMove.clientId);
		if(!player) {
			return;
		}


		((ControllerServerPlayer*)player->getController())->moveEvent(packetMove);

	}

}

void Server::handleTickBuffer() {

	std::vector<Player*> players = myContainer->getPlayersManager()->getPlayers();
	for(int i = 0; i < players.size(); i++) {

		PlayerPacket packet;
		packet.publicId = players[i]->getPublicId();
		packet.x = players[i]->getX();
		packet.y = players[i]->getY();
		packet.loadToStream();
		myContainer->getYuPacketManager()->addToTickBuffer(packet.getStream());

	}
	myContainer->getYuPacketManager()->buildTicksBufferStream();

	std::vector<YuNetwork::YuClient*> clients = myContainer->getClientsManager()->getClients();
	for(int i = 0; i < clients.size(); ++i) {

		serverHandler->sendTickPacketStream(clients[i]);

	}
	myContainer->getYuPacketManager()->resetTickBuffer();

}


void Server::loop() {
	int timeout = 60*60;

	YuNetwork::ClientsManager* clientsManager = new YuNetwork::ClientsManager(myContainer);
	myContainer->setClientsManager(clientsManager);

	YuNetwork::YuPacketManager packetManager(myContainer);
	myContainer->setYuPacketManager(&packetManager);

	serverHandler = new YuNetwork::ServerHandler(myContainer, 1234);

	playersManager = new PlayersManager(myContainer);
	myContainer->setPlayersManager(playersManager);

	YuEngine::FpsCounter fpsCounter;

	int ticks = 0;

	while(true) {
		int startTime = SDL_GetTicks();
		ticks++;
		clientsManager->update();
		fpsCounter.update();
		playersManager->update();


		handleNewClients();

		handleTickBuffer();
		updateClients();

		int endTime = SDL_GetTicks();
		int elapsedTime = endTime - startTime;
		float frameRate = (1000.0f/30.0f);
		if(elapsedTime < frameRate) {
			SDL_Delay(frameRate - elapsedTime);
		}
	
	}

}