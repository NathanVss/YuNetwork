#include "MainScene.h"
#include "MyContainer.h"

#include <iostream>

#include <Noxel-OpenGL\YuEngine\GameRenderer.h>
#include <Noxel-OpenGL\YuEngine\DebugOverlay.h>
#include <Noxel-OpenGL\YuEngine\FpsCounter.h>
#include <Noxel-OpenGL\YuEngine\Shader.h>
#include <Noxel-OpenGL\YuEngine\Camera2D.h>
#include <Noxel-OpenGL\YuEngine\Input.h>
#include <Noxel-OpenGL\YuEngine\SpritesheetsManager.h>
#include <Noxel-OpenGL\YuEngine\Spritesheet.h>
#include <Noxel-OpenGL\YuEngine\YuBoudingbox.h>


#include <YuNetwork\YuPacket.h>
#include <YuNetwork\YuPacketManager.h>
#include <YuNetwork\ClientsManager.h>
#include <YuNetwork\YuClient.h>
#include <YuNetwork\StringStream.h>
#include <YuNetwork\ClientHandler.h>

#include "ControllerClientPlayer.h"
#include "ControllerClientPackets.h"

#include "Player.h"
#include "PlayersManager.h"
#include "PlayerMP.h"

MainScene::MainScene(void) : OpenGlScene(1280,720, "YuNetwork Dev") {
	frameRate = ( 1000 / 60.0f);
	container = new MyContainer();

	init(container);
	loop();
}


MainScene::~MainScene(void)
{
}

void MainScene::loop() {

	bool multi = true;
	int timeout = 60*60;
	int ticks = 0;

	if(multi) {
		std::string ip("192.168.1.10");
		clientHandler = new YuNetwork::ClientHandler(container);
		container->setClientHandler(clientHandler);

		YuNetwork::YuPacketManager packetManager;
		container->setYuPacketManager(&packetManager);

		controllerClientPlayer = new ControllerClientPlayer(container);
		container->setControllerClientPlayer(controllerClientPlayer);

		controllerClientPackets = new ControllerClientPackets(container);
		controllerClientPackets->attachControllerPlayer(controllerClientPlayer);
	}


	gameRenderer->init();

	YuEngine::FpsCounter fpsCounter;

	playersManager = new PlayersManager(container);
	container->setPlayersManager(playersManager);


	glViewport(0, 0, width, height);
	while(true) {
		beginIteration();

		ticks++;

		if(multi) {


			clientHandler->update();

			if(clientHandler->getClient()->isConnected()) {
				controllerClientPackets->update();

				container->getYuPacketManager()->buildBufferStream();
				clientHandler->sendPacketStream();
				container->getYuPacketManager()->resetBuffer();
			}

		}
		controllerClientPlayer->update();
		//playersManager->update();
		container->getInput()->update();
		debugOverlay->update();
		fpsCounter.update();
		container->getCamera()->setPosition(glm::vec2(0,0));
		container->getCamera()->update();


		glClearColor(0.5f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		gameRenderer->begin();

			debugOverlay->addDebugString(std::string("FPS : ") + std::to_string(fpsCounter.getLastFps()));
			debugOverlay->addDebugString(std::string("Packets : ") + std::to_string(YuNetwork::YuPacket::packetsTotal));

			debugOverlay->render();


			playersManager->render();
			controllerClientPlayer->render();

			container->getClassicShader()->use();
			container->getClassicShader()->sendMatrix4("cameraMatrix", container->getCamera()->getCameraMatrix());

			gameRenderer->end();

			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			gameRenderer->render(container->getClassicShader()->getProgramID());


		container->getClassicShader()->unuse();


		endIteration();
		

	}
}