#pragma once
#include <dependecies\SDL2-2.0.3\include\SDL_net.h>
#include <string>

#include "YuSocket.h"

namespace YuNetwork {

class YuClient {

private:
	YuSocket clientSocket;
	int publicId;
	std::string clientId;

	bool connected;

	int lastLifeSign;
	int timeout;
public:
	YuClient(YuSocket clientSocket_, int _timeout) {
		clientSocket = clientSocket_;
		publicId = 0;
		connected = false;

		timeout = _timeout;
		lastLifeSign = 0;
		publicId = 0;
	};
	YuClient() {

	};
	~YuClient() {

	};

	YuSocket* getClientSocket() {
		return &clientSocket;
	}

	void update() {
		lastLifeSign++;
	};

	void newLifeSign() {
		lastLifeSign = 0;
	}

	bool isLost() {
		return lastLifeSign > timeout;
	}

	YuSocket* getSocket() {
		return &clientSocket;
	}

	//void setId(std::string _id) {

	//	id = _id;
	//}

	//std::string getId() {
	//	return id;
	//}

	void setPublicId(int i) {

		publicId = i;
	}

	int getPublicId() {
		return publicId;
	}
	void setClientId(std::string id) {
		clientId = id;
	}
	std::string getClientId() {
		return clientId;
	}

	bool isConnected() {
		return connected;
	}
	void setConnected(bool flag) {
		connected = flag;
	}


};

}