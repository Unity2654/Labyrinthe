#pragma once
#include "Collidable.h"
#include <vector>

namespace gloop {
	/** Data returned by the physics collision methods
	  * collision : Vector to apply to the movement to simulate the collision
	  * correction : Correction to prevent objects from sinking into one another
	  */
	struct collisionData {
		Vector2f collision{ 0,0 };
		Vector2f correction{ 0,0 };
	};

	class Physics {
	public :
		Physics() = delete;

		// Methods

		// Collision between two objects. The data only concerns the main object.
		static collisionData collide(const Collidable& mainObject, const Collidable& otherObject);
		// Collision between one object, and muliple others.
		static collisionData collide(const Collidable& mainObject, const std::vector<const Collidable&> otherObjects);
	};
}