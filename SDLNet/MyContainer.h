#pragma once

#include <Noxel-OpenGL\YuEngine\Container.h>
#include <YuNetwork\Container.h>

class PlayersManager;
class ServerPlayersManager;
class ControllerClientPlayer;

class MyContainer : public YuNetwork::Container, public YuEngine::Container
{
public:
	MyContainer(void);
	~MyContainer(void);
	void setPlayersManager(PlayersManager* p) {
		playersManager = p;
	}
	PlayersManager* getPlayersManager() {
		return playersManager;
	}

	void setControllerClientPlayer(ControllerClientPlayer* c) {

		controllerClientPlayer = c;
	}
	ControllerClientPlayer* getControllerClientPlayer() {

		return controllerClientPlayer;
	}

private:
	PlayersManager* playersManager;
	ControllerClientPlayer* controllerClientPlayer;
};

