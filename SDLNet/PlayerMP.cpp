#include "PlayerMP.h"
#include "Packets.h"

PlayerMP::PlayerMP(void) {
}

PlayerMP::PlayerMP(MyContainer* c) : Player(c) {
	moveId = 0;
	connected = false;

}


PlayerMP::~PlayerMP(void)
{
}

void PlayerMP::handlePlayerPacket(PlayerPacket* packet) {

	//for(int i = 0; i < syncPositions.size(); i++) {

	//	if(syncPositions[i].id == packet->

	//}

}

/*
 * Synchronisation de la position actuelle avec le buffer ( Client & Server )
 */
void PlayerMP::syncPosition(int id) {
	if(connected) {

		syncPositions.push_back(SyncPosition(x, y, moveId));
		if(syncPositions.size() > 50) {
			syncPositions.erase(syncPositions.begin(), syncPositions.begin() + 1);
		}
		std::cout << "Size : " << syncPositions.size() << std::endl;
		std::cout << "Pos[" << syncPositions[syncPositions.size()-1].x << ";" << syncPositions[syncPositions.size()-1].y << "] #" << syncPositions[syncPositions.size()-1].id << std::endl;

	}

}

/*
 * Envois d'un packet de mouvement Client -> Server
 */
void PlayerMP::sendMovePacket() {
	PacketMove packetmove;
	packetmove.id = moveId;
	packetmove.clientId = clientSocket->getClientId();
	packetmove.publicId = clientSocket->getPublicId();
	packetmove.velocityX = velocityX;
	packetmove.velocityY = velocityY;
	packetmove.loadToStream();
	myContainer->getYuPacketManager()->addToBuffer(packetmove.getStream());
}



void PlayerMP::update() {
	Player::update();

	moveId++;
	syncPosition(moveId);

	if(location == PlayerLocation::CLIENT && connected) {

		sendMovePacket();
	}
}

void PlayerMP::setClientSocket(YuNetwork::YuClientSocket* s) {
	clientSocket = s;
}
