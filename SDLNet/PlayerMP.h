#pragma once

#include "Player.h"

class SyncPosition {
public:
	SyncPosition(float _x, float _y, int _id) : x(_x), y(_y), id(_id) {

	};
	~SyncPosition() {
	};
	int id;
	float x;
	float y;
};

enum class PlayerLocation {

	SERVER,
	CLIENT

};

class PlayerMP : public Player
{
protected:
	YuNetwork::YuClientSocket* clientSocket;
	PlayerLocation location;
	

	int moveId;
	int publicId;
	bool connected;
	std::vector<SyncPosition> syncPositions;

public:
	PlayerMP();
	PlayerMP(MyContainer* c);
	~PlayerMP(void);

	void syncPosition(int id);
	void sendMovePacket();
	virtual void update();

	void setClientSocket(YuNetwork::YuClientSocket* s);

	void handlePlayerPacket(PlayerPacket* pack);

	void setLocation(PlayerLocation l) {
		location = l;
	}

	void setConnected(bool flag) {
		connected = flag;
	}

	void setPublicId(int id) {
		publicId = id;
	}
	int getPublicId() {

		return publicId;
	}


};

