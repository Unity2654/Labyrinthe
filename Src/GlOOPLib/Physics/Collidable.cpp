#include "Collidable.h"
#include <GL/gl.h>
#include <iostream>

namespace gloop{
	void Collidable::drawHitbox(float height) const{
		Rectangle hb = getCollisionBox().hitbox;
		glPushMatrix();
		//std::cout << hb.position.x << " " << hb.position.y << std::endl << std::endl;
		glTranslatef(hb.getPosition().x, 0.0, hb.getPosition().y);
		glScalef(hb.getWidth(), height, hb.getHeight());

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