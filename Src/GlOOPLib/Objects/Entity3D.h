#pragma once
#include "Object3D.h"

namespace gloop {

	/**
	 * Extension of a 3D object.
	 * A 3D Object is destined to be static, whereas an entity is destined to be updated
	 */
	class Entity3D : public Object3D{
	public:
		virtual void update() = 0;
	};
}