#pragma once
#include <vector>
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
		virtual double getMass() const { return 0; }

		virtual Rectangle getCollisionBox() const { return Rectangle(gloop::Vector2f{ 0.0,0.0 }, 0.0, 0.0); }

		virtual Vector2f getSpeed() const { return Vector2f{ 0,0 }; };
	};

}