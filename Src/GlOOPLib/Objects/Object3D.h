#pragma once
#include <string>
#include <iostream>

namespace gloop {

	 // Class defining an object in 3 dimensions, with a simple API to manipulate it.
	 // It is destined to be inherited to be used to actually render something.
	class Object3D {
	public :
		virtual void render() {};
	};
}