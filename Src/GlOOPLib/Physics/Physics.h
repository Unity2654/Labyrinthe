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
		bool collisionOccured = false;

		collisionData& operator+=(collisionData& other) {
			collision = collision + other.collision;
			correction = collision + other.correction;
			collisionOccured = collisionOccured || other.collisionOccured;
			return *this;
		}
	};

	class Physics {
	private :
		static constexpr float Skin = 0.0f; // Penetration threshold for a collision to be considered
		static constexpr float epsilon = 0.0f; // minimum to avoid float errors
		static constexpr float correctionCoeff = 1.2f; // Coefficient for the correction applied to the objects
		static constexpr float restitution = 0.02f; // "bounciness" coefficient of the objects
		
		struct Penetration {
			Vector2f normal;
			float depth;
		};

		// Computes the collision between two Rectangles, and returns the important informations about the collision
		static bool doCollide(const Rectangle& lhs, const Rectangle& rhs, Penetration& p);

	public :
		Physics() = delete;

		// Methods

		// Collision between two objects. The data only concerns the main object.
		static collisionData collide(const Collidable& mainObject, const Rectangle& otherObject);
		// Collision between one object, and muliple others.
		static collisionData collide(const Collidable& mainObject, const std::vector<Rectangle>& otherObjects);
	};
}