#include "Collidable.h"
#include <GL/gl.h>
#include <iostream>

namespace gloop{
	Rectangle::Rectangle(Vector2f position, float width, float height) :
		height(height),
		width(width),
		position(position){}

	Rectangle Rectangle::fromCenter(Vector2f center, float width, float height)
	{
		Vector2f TopLeft{center.x - width / 2, center.y - height / 2};
		return Rectangle(TopLeft, width, height);
	}

	Rectangle Rectangle::fromUrDlCorners(Vector2f upRightCorner, Vector2f downLeftCorner){
		Vector2f TopLeft{ upRightCorner.x, downLeftCorner.y };
		return Rectangle(TopLeft, upRightCorner.x - downLeftCorner.x, upRightCorner.y - downLeftCorner.y);
	}

	Rectangle Rectangle::fromUlDrCorners(Vector2f upLeftCorner, Vector2f downRightCorner){
		return Rectangle(upLeftCorner, downRightCorner.x - upLeftCorner.x, upLeftCorner.y - downRightCorner.y);
	}

	Vector2f Rectangle::getCenter() const{
		return Vector2f{ position.x + width / 2, position.y - height / 2 };
	}
	std::vector<Vector2f> Rectangle::getCorners() const{
		return std::vector<Vector2f>{
			position, // Top left
			Vector2f{position.x + width, position.y}, // Top right
			Vector2f{position.x, position.y - height}, // Bottom left
			Vector2f{position.x + width, position.y - height} // Bottom right
		};
	}
	float Rectangle::getSize() const{
		return height * width;
	}

	Vector2f Rectangle::getDiagonal() const{
		return Vector2f::absolute(Vector2f{ position.x + width, position.y - height } - position);
	}

	void Collidable::drawHitbox(float height) const{
		Rectangle hb = getCollisionBox().hitbox;
		glPushMatrix();
		//std::cout << hb.position.x << " " << hb.position.y << std::endl << std::endl;
		glTranslatef(hb.position.x, 0.0, hb.position.y);
		glScalef(hb.width, height, hb.height);

		int polygonMode[2];
		glGetIntegerv(GL_POLYGON_MODE, polygonMode);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glBegin(GL_QUADS);
		glNormal3f(-1.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 1.0, 1.0);
		glVertex3f(0.0, 1.0, 0.0);

		glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(1.0, 0.0, 0.0);
		glVertex3f(1.0, 0.0, 1.0);
		glVertex3f(1.0, 1.0, 1.0);
		glVertex3f(1.0, 1.0, 0.0);

		glNormal3f(0.0, 0.0, -1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(1.0, 0.0, 0.0);
		glVertex3f(1.0, 1.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);

		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 0.0, 1.0);
		glVertex3f(1.0, 0.0, 1.0);
		glVertex3f(1.0, 1.0, 1.0);
		glVertex3f(0.0, 1.0, 1.0);
		glEnd();

		glPolygonMode(GL_FRONT, polygonMode[0]);
		glPolygonMode(GL_BACK, polygonMode[1]);

		glPopMatrix();
	}
}