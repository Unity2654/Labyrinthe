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
	private :
		struct Penetration {
			Vector2f normal;
			float depth;
		};

		// Computes the collision between two Rectangles, and returns the important informations about the collision
		bool doCollide(const Rectangle& lhs, const Rectangle& rhs, Penetration& p);

	public :
		Physics() = delete;

		// Methods

		// Collision between two objects. The data only concerns the main object.
		static collisionData collide(const Collidable& mainObject, const Rectangle& otherObject);
		// Collision between one object, and muliple others.
		static collisionData collide(const Collidable& mainObject, const std::vector<Rectangle>& otherObjects);
	};
}