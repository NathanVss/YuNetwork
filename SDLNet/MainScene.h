#pragma once

#include <Noxel-OpenGL\YuEngine\OpenGlScene.h>
#include <string>

class MyContainer;
class PlayerMP;
class PlayersManager;
class ControllerClientPlayer;
class ControllerClientPackets;

#include <YuNetwork\ClientHandler.h>


class MainScene : public YuEngine::OpenGlScene
{
public:
	MainScene(void);
	virtual ~MainScene(void);
	void loop();
	void checkSocket();
	void handlePacket(std::string &stream, int packetId);

protected:
	YuNetwork::ClientHandler* clientHandler;
	PlayersManager* playersManager;
	MyContainer* container;
	ControllerClientPlayer* controllerClientPlayer;
	ControllerClientPackets* controllerClientPackets;
};

