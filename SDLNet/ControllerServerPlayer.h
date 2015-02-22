#pragma once

#include "IControllerPlayer.h"
#include "Packets.h"
class Player;

class ControllerServerPlayer : public IControllerPlayer
{
private:
	Player* player;

public:
	ControllerServerPlayer(void);
	ControllerServerPlayer(MyContainer* c, Player* player);
	~ControllerServerPlayer(void);

	void moveEvent(PacketMove packet);
	virtual void update();
	virtual void render();
};

