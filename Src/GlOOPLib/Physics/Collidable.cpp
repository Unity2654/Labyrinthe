#include "Collidable.h"

namespace gloop{
	Rectangle::Rectangle(Vector2f position, double width, double height) :
		height(height),
		width(width),
		position(position){}

	Rectangle Rectangle::fromCenter(Vector2f center, double width, double height)
	{
		Vector2f TopLeft{center.x - width / 2, center.y - height / 2};
		return Rectangle(TopLeft, width, height);
	}


}