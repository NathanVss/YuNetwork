#pragma once

#include "MyContainer.h"

class Object
{
public:
	Object() {

	};
	Object(MyContainer* container) {
		myContainer = container;
	};
	~Object(void) {

	};
protected:
	MyContainer* myContainer;
};
