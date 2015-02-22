#pragma once

#include "Object.h"

class IControllerPlayer : public Object
{

public:
	IControllerPlayer(void);
	IControllerPlayer(MyContainer* c);
	~IControllerPlayer(void);

	virtual void update() = 0;
	virtual void render() = 0;
};

