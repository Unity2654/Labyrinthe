#include "Collidable.h"

namespace gloop{
	Rectangle::Rectangle(Vector3f position, double width, double height) :
		height(height),
		width(width),
		position(position){}

	Rectangle Rectangle::fromCenter(Vector3f center, double width, double height)
	{

		return Rectangle();
	}


}