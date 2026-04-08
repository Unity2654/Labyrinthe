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

	class Collidable {
	public :
		virtual CollisionBox getCollisionBox() const = 0;

		void drawHitbox(float height) const;
	};

	enum CollisionFlag {

	};

	struct CollisionBox {	
		const Rectangle hitbox;
		const bool isSolid = true;
		const std::set<CollisionFlag> flags = {};
		const Vector2f speed{ 0.0,0.0 };
	};
}