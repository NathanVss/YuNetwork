#pragma once

#include "Object.h"
#include "MyContainer.h"
#include <Noxel-OpenGL\YuEngine\GameRenderer.h>
#include <Noxel-OpenGL\YuEngine\SpritesheetsManager.h>
#include <Noxel-OpenGL\YuEngine\Spritesheet.h>

#include <Noxel-OpenGL\YuEngine\Input.h>

#include "IControllerPlayer.h"

class Player : public Object
{
public:
	Player(MyContainer* c) : Object(c) {
		x = 0;
		y = 0;
		velocityX = 0;
		velocityY = 0;
		width = 100;
		height = 100;
		ticks = 0;
		local = false;
		publicId = 0;

	};
	Player() {

	};
	~Player(void) {

	};


	void render() {

		myContainer->getGameRenderer()->addGlyph(x,y,width,height,15,1.0f,1.0f,1.0f,1.0f, myContainer->getSpritesheetsManager()->getBlocksSpritesheet(), 0,0,1,1);

	}

	virtual void update() {
		ticks++;

		x += velocityX;
		y += velocityY;


	}

	void setVelocityX(float _x) {
		velocityX = _x;
	}
	void setVelocityY(float _y) {
		velocityY = _y;
	}
	void setVelocity(float _x, float _y) {
		velocityX = _x;
		velocityY = _y;
	}

	void setPosition(float _x, float _y) {
		x = _x;
		y = _y;
	}

	virtual float getX() {
		return x;

	}
	virtual float getY() {
		return y;
	}

	void setLocal(bool flag) {
		local = flag;
	}
	bool getLocal() {
		return local;
	}
	void setController(IControllerPlayer* c) {
		iController = c;
	}
	IControllerPlayer* getController() {
		return iController;
	}

	void setPublicId(int id) {
		publicId = id;
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
	float getVelocityX() {
		return velocityX;
	}
	float getVelocityY() {
		return velocityY;
	}


protected:
	int ticks;
	float width;
	float height;
	float x;
	float y;
	float velocityX;
	float velocityY;
	bool local;
	IControllerPlayer* iController;
	int publicId;
	std::string clientId;


};

