#pragma once

#include "Vector.h"
#include <vector>

namespace gloop {
	// A rectangle, destined to be used to store the data of a hitbox for collisions  
	struct Rectangle {
	private :
		Vector2f position;
		float width;
		float height;

	public:

		// Constructors
		Rectangle() = delete;
		// Constructs a rectangle from its up left corner, and its width/height
		Rectangle(Vector2f position, float width, float height);

		static Rectangle fromCenter(Vector2f center, float width, float height);
		// Construct a rectangle from its up right and down left corners
		static Rectangle fromUrDlCorners(Vector2f upRightCorner, Vector2f downLeftCorner);
		// Construct a rectangle from its up left and down right corners
		static Rectangle fromUlDrCorners(Vector2f upLeftCorner, Vector2f downRightCorner);

		Vector2f getCenter() const;

		const Vector2f getPosition() const { return position; }
		const float getWidth() const { return width; }
		const float getHeight() const { return height; }

		// Checks if the given position is located within the rectangle's boudaries
		bool isWithin(const Vector2f& position) const;

		//Gets a vector containing the four corners of the square in the following order : { UL, UR, DL, DR }
		std::vector<Vector2f> getCorners() const;

		float getSize() const;

		Vector2f getDiagonal() const;
	};
}