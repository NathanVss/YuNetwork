#include "ControllerSinglePlayer.h"
#include "Player.h"
#include "PlayersManager.h"

ControllerSinglePlayer::ControllerSinglePlayer(void){
}

ControllerSinglePlayer::ControllerSinglePlayer(MyContainer* c ) : IControllerPlayer(c) {
	localPlayer = new Player(c);
	localPlayer->setLocal(true);
	localPlayer->setController(this);
	//myContainer->getPlayersManager()->handleNewPlayer(localPlayer);
}

ControllerSinglePlayer::~ControllerSinglePlayer(void)
{
}

void ControllerSinglePlayer::update() {

	float speed = 10;

	localPlayer->setVelocity(0,0);
	if(myContainer->getInput()->getKey(YuEngine::KeyName::z)) {
		localPlayer->setVelocityY(speed);
	}
	if(myContainer->getInput()->getKey(YuEngine::KeyName::s)) {
		localPlayer->setVelocityY(-speed);
	}
	if(myContainer->getInput()->getKey(YuEngine::KeyName::q)) {
		localPlayer->setVelocityX(-speed);
	}
	if(myContainer->getInput()->getKey(YuEngine::KeyName::d)) {
		localPlayer->setVelocityX(speed);
	}

	localPlayer->update();
	std::cout << " Pos[" << localPlayer->getX() << ";" << localPlayer->getY() << "]" << std::endl;


}

void ControllerSinglePlayer::render() {
	localPlayer->render();
}