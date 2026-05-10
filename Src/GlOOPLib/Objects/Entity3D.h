#pragma once
#include "Object3D.h"

namespace gloop {

	// Extension of a 3D object.
	// A 3D Object is destined to be static, whereas an entity is destined to be updated every frame
	class Entity3D : public Object3D{
	public:
		// Function called each time the entity should be updated
		virtual void update() {};
	};
}