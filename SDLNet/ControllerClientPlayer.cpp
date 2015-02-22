#include "ControllerClientPlayer.h"
#include "Player.h"
#include <YuNetwork\YuPacketManager.h>

ControllerClientPlayer::ControllerClientPlayer(void)
{
}

ControllerClientPlayer::ControllerClientPlayer(MyContainer* c) : ControllerSinglePlayer(c) {


}



ControllerClientPlayer::~ControllerClientPlayer(void)
{
}

void ControllerClientPlayer::authAction(YuNetwork::YuAuthPacket packet) {

	localPlayer->setPublicId(packet.publicId);
	localPlayer->setClientId(packet.clientId);

}


void ControllerClientPlayer::update() {
	ControllerSinglePlayer::update();

	PacketMove packet;
	packet.clientId = localPlayer->getClientId();
	packet.publicId = localPlayer->getPublicId();
	packet.velocityX = localPlayer->getVelocityX();
	packet.velocityY = localPlayer->getVelocityY();
	packet.loadToStream();

	myContainer->getYuPacketManager()->addToBuffer(packet.getStream());
	std::cout << " Pos[" << localPlayer->getX() << ";" << localPlayer->getY() << "]" << std::endl;

}

void ControllerClientPlayer::render() {
	ControllerSinglePlayer::render();

}