#include "PlayersManager.h"
#include "Packets.h"


PlayersManager::PlayersManager(MyContainer* c) : Object(c)
{
}


PlayersManager::~PlayersManager(void)
{
}


void PlayersManager::handleNewPlayer(Player* p) {
	players.push_back(p);
}

Player* PlayersManager::getLocalPlayer() {
	for(int i = 0; i < players.size(); i++) {
		if(players[i]->getLocal()) {
			return players[i];
		}
	}
	return nullptr;
}

Player* PlayersManager::newPlayer() {
	Player* player = new Player(myContainer);

	handleNewPlayer(player);
	return player;

}

std::vector<Player*>& PlayersManager::getPlayers() {
	return players;
}


Player* PlayersManager::getPlayer(int publicId) {
	for(int i = 0; i < players.size(); i++) {
		if(players[i]->getPublicId() == publicId) {
			return players[i];
		}
	}
	return nullptr;
}
Player* PlayersManager::getPlayer(std::string clientId) {
	for(int i = 0; i < players.size(); i++) {
		if(players[i]->getClientId() == clientId) {
			return players[i];
		}
	}
	return nullptr;
}

/*
 * Render the other players
 */
void PlayersManager::render() {

	for(int i = 0; i < players.size(); i++) {

		players[i]->render();
	}
}


/*
 * Outdated, needless to update other players since they are directed by server
 */
void PlayersManager::update() {

	for(int i = 0; i < players.size(); i++) {

	}
}