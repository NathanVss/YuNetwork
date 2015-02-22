#pragma once

#include "ControllerSinglePlayer.h"
#include "Packets.h"
class ControllerClientPlayer : public ControllerSinglePlayer
{
public:
	ControllerClientPlayer(void);
	ControllerClientPlayer(MyContainer* c);
	~ControllerClientPlayer(void);

	virtual void update();
	virtual void render();
	void authAction(YuNetwork::YuAuthPacket packet);
};

