#pragma once

#include "Object.h"
#include <vector>
#include "Player.h"
#include "MyContainer.h"

#include "Packets.h";

class PlayersManager : public Object
{
public:
	PlayersManager(MyContainer* c);
	~PlayersManager(void);
	
	void handleNewPlayer(Player* p);
	Player* getLocalPlayer();
	Player* getPlayer(int publicId);
	Player* getPlayer(std::string clientId);
	Player* newPlayer();
	std::vector<Player*>& getPlayers();
	virtual void render();
	virtual void update();

protected:
	std::vector<Player*> players;
};

