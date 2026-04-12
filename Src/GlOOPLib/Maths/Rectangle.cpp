#include "Rectangle.h"
#include <vector>
#include <iostream>

namespace gloop {
	Rectangle::Rectangle(Vector2f position, float width, float height) :
		height(height),
		width(width),
		position(position) {
	}

	Rectangle Rectangle::fromCenter(Vector2f center, float width, float height)
	{
		Vector2f TopLeft{ center.x - width / 2, center.y - height / 2 };
		return Rectangle(TopLeft, width, height);
	}

	Rectangle Rectangle::fromUrDlCorners(Vector2f upRightCorner, Vector2f downLeftCorner) {
		Vector2f TopLeft{ upRightCorner.x, downLeftCorner.y };
		return Rectangle(TopLeft, upRightCorner.x - downLeftCorner.x, upRightCorner.y - downLeftCorner.y);
	}

	Rectangle Rectangle::fromUlDrCorners(Vector2f upLeftCorner, Vector2f downRightCorner) {
		return Rectangle(upLeftCorner, downRightCorner.x - upLeftCorner.x, upLeftCorner.y - downRightCorner.y);
	}

	Vector2f Rectangle::getCenter() const {
		return Vector2f{ position.x + width / 2, position.y - height / 2 };
	}
	bool Rectangle::isWithin(const Vector2f& position) const{
		// X axis
		if (position.x < this->position.x || position.x > (this->position.x + width))
			return false;
		// Y axis
		if (position.y < this->position.y || position.y > (this->position.y + height))
			return false;
		return true;
	}

	std::vector<Vector2f> Rectangle::getCorners() const {
		return std::vector<Vector2f>{
			position, // Top left
				Vector2f{ position.x + width, position.y }, // Top right
				Vector2f{ position.x, position.y - height }, // Bottom left
				Vector2f{ position.x + width, position.y - height } // Bottom right
		};
	}
	float Rectangle::getSize() const {
		return height * width;
	}

	Vector2f Rectangle::getDiagonal() const {
		return Vector2f::absolute(Vector2f{ position.x + width, position.y - height } - position);
	}
}