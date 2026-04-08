#pragma once
#include <vector>
#include <set>
#include "../Maths/Vector.h"


namespace gloop {

	// A rectangle, destined to be used to store the data of a hitbox for collisions  
	struct Rectangle {
	public:
		const Vector2f position;
		const float width;
		const float height;

		// Constructors
		Rectangle() = delete;
		/**
	     * Constructs a rectangle from its up left corner, and its width/height 
		 */
		Rectangle(Vector2f position, float width, float height);
		
		static Rectangle fromCenter(Vector2f center, float width, float height);
		/**
		 * Construct a rectangle from its up right and down left corners
		 */
		static Rectangle fromUrDlCorners(Vector2f upRightCorner, Vector2f downLeftCorner);
		/**
		 * Construct a rectangle from its up left and down right corners
		 */
		static Rectangle fromUlDrCorners(Vector2f upLeftCorner, Vector2f downRightCorner);

		Vector2f getCenter() const;

		/**
		 * Gets a vector containing the four corners of the square in the following order : { UL, UR, DL, DR }
		*/
		std::vector<Vector2f> getCorners() const;

		float getSize() const;

		Vector2f getDiagonal() const;
	};

	// Collision flags
	// Add more flags to this enum when necessary.
	enum CollisionFlag {

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