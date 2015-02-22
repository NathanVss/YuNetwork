#pragma once

#include "IControllerPlayer.h"

class Player;

class ControllerSinglePlayer : public IControllerPlayer
{
public:
	ControllerSinglePlayer(void);
	ControllerSinglePlayer(MyContainer* c);
	~ControllerSinglePlayer(void);

	Player* getPlayer() {
		return localPlayer;
	}
	virtual void update();
	virtual void render();

protected:
	Player* localPlayer;

};

