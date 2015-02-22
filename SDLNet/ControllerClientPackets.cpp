#include "ControllerClientPackets.h"
#include "MyContainer.h"
#include <YuNetwork\ClientHandler.h>
#include <YuNetwork\YuPacketManager.h>
#include "ControllerClientPlayer.h"
#include "Packets.h"
#include "Player.h"
#include "PlayersManager.h"

ControllerClientPackets::ControllerClientPackets(void){
}

ControllerClientPackets::ControllerClientPackets(MyContainer* c) : Object(c){



}


ControllerClientPackets::~ControllerClientPackets(void)
{
}


void ControllerClientPackets::update() {

	if(myContainer->getClientHandler()->isReady()) {

		std::vector<std::string> bufferReceived = myContainer->getClientHandler()->receive();
		for(int k = 0; k < bufferReceived.size(); k++) {

			std::vector<int> packetIds = myContainer->getYuPacketManager()->getPacketsIds(bufferReceived[k]);

			for(int i = 0; i < packetIds.size(); i++) {

				std::string curStream =  myContainer->getYuPacketManager()->getPacketString(i, bufferReceived[k]);
				handlePacket(curStream, packetIds[i]);
			}
		}
	}

}

void ControllerClientPackets::handlePacket(std::string &stream, int packetId) {

	if(packetId == YuNetwork::YuPacket::yuAuthPacketId) {
		YuNetwork::YuAuthPacket auth;
		auth.loadStream(stream);
		auth.readFromStream();

		myContainer->getClientHandler()->getClient()->setClientId(auth.clientId);
		myContainer->getClientHandler()->getClient()->setPublicId(auth.publicId);

		myContainer->getControllerClientPlayer()->authAction(auth);
	
		std::cout << "Connected to host." << std::endl;
	}
	if(packetId == PacketIds::packetPlayerId) {
		
		PlayerPacket playerPacket;
		playerPacket.loadStream(stream);
		playerPacket.readFromStream();

		if(playerPacket.publicId == myContainer->getControllerClientPlayer()->getPlayer()->getPublicId()) {
			return;
		}

		Player* player = myContainer->getPlayersManager()->getPlayer(playerPacket.publicId);
		if(!player) {
			player = myContainer->getPlayersManager()->newPlayer();
			player->setPublicId(playerPacket.publicId);
		}
		
		player->setPosition(playerPacket.x, playerPacket.y);

	}

}