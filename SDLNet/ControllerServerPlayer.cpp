#include "ControllerServerPlayer.h"
#include "Player.h"

ControllerServerPlayer::ControllerServerPlayer(void)
{
}

ControllerServerPlayer::ControllerServerPlayer(MyContainer* c, Player* _player) : IControllerPlayer(c){
	player = _player;
}

ControllerServerPlayer::~ControllerServerPlayer(void)
{
}

void ControllerServerPlayer::moveEvent(PacketMove packet) {

	player->setPosition(player->getX() + packet.velocityX, player->getY() + packet.velocityY);
	std::cout << " Pos[" << player->getX() << ";" << player->getY() << "]" << std::endl;
}


void ControllerServerPlayer::update() {
	//std::cout << "Update" << std::endl;
}

void ControllerServerPlayer::render() {


}