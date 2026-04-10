#pragma once
#include <vector>
#include <set>
#include "../Maths/Vector.h"
#include "../Maths/Rectangle.h"

namespace gloop {

	// Collision flags
	// Add more flags to this enum when necessary.
	enum CollisionFlag {
		TESTFLAG, // Flag used for testing puposes, don't use in practice
	};

	// Hitbox of an object
	struct CollisionBox {
		const Rectangle hitbox; // Rectangle allowing to check wether a collision occured or not.
		const bool isSolid = true; // If the object is not solid, the collision is taken into account, but not resolved
		const std::set<CollisionFlag> flags = {}; // Flags of the object. If a collision occur, the flags will appear in the result, even if the object is not solid
		const Vector2f speed{ 0.0,0.0 }; // Speed of the object, if it's moving.
	};

	// Abstract class that allow objects to have collisions between each other
	class Collidable {
	public :
		// Returns the hitbox of the object
		virtual CollisionBox getCollisionBox() const = 0;

		// Draws the hitbox of the object
		// The hitbox is a rectangle, the height parameter is the height of the solid that will be drawn, so it's more visible than a square on the ground
		void drawHitbox(float height) const;
	};
}