#include <iostream>
#include <dependecies\SDL2-2.0.3\include\SDL.h>
#include <dependecies\SDL2-2.0.3\include\SDL_net.h>
#include <vector>
#include "MainScene.h"
#include "Server.h"

int main(int argc, char **argv) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDLNet_Init();

	bool server = true;

	char response = 'c';

	std::cout << std::endl << "Server(s) , Client(c) ? ";
	std::cin >> response;
	if(response == 'c') {
		server = false;
	} else {
		server = true;
	}

	int timeout = 60*60;





	/** CLIENT **/

	if(!server) {

		MainScene mainScene;

	} else {
		
		Server server;
	}
	

	system("pause");
	return 1;
}