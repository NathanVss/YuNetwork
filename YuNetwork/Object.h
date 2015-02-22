#pragma once

#include "Container.h"

namespace YuNetwork {

class Container;


class Object
{
public:
	Object() {

	};
	Object(Container* c) {
		container = c;
	}
	~Object(void) {


	};

protected:
	Container* container;
};

}