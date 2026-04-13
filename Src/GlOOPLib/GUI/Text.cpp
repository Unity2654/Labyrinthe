#include "Text.h"
#include <GL/gl.h>
#include <corecrt_math_defines.h>
#include <cmath>
#include "../Lights/Materials.h"
#include <iostream>

void crescent(float px, float py, float scale, float rotation = 1.0) {
	glPushMatrix();
	glTranslatef(px, py, 0);

	float angle = M_PI;
	float target = angle + M_PI;
	scale = 0.5 * scale * rotation;
	float step = 0.1f;
	float fullness = 0.6f;
	glBegin(GL_TRIANGLE_STRIP);
	while (angle < target) {
		glVertex2f(scale * sinf(angle), scale * cosf(angle));
		glVertex2f(fullness * scale * sinf(angle), scale * cosf(angle));
		angle += step;
	}
	glEnd();

	glPopMatrix();
}

void gloop::glyphs::A(){
	glBegin(GL_QUADS);
	
	glVertex2f(0.5,-0.5);
	glVertex2f(0.4,-0.5);
	glVertex2f(0.0,0.3);
	glVertex2f(0.0,0.5);

	glVertex2f(-0.5, -0.5);
	glVertex2f(-0.4, -0.5);
	glVertex2f(0.0, 0.3);
	glVertex2f(0.0, 0.5);

	glVertex2f(-0.3, 0.0);
	glVertex2f(0.3, 0.0);
	glVertex2f(0.3, -0.1);
	glVertex2f(-0.3, -0.1);

	glEnd();
}

void gloop::glyphs::B(){
	glBegin(GL_QUADS);
	
	glVertex2f(0.38, -0.5);
	glVertex2f(0.3, -0.5);
	glVertex2f(0.3, 0.5);
	glVertex2f(0.38, 0.5);

	glEnd();

	crescent(0.2,-0.25,0.5);
	crescent(0.2, 0.25, 0.5);
}

void gloop::glyphs::C(){
	crescent(0, 0, 1.0, -1.0);
}

void gloop::glyphs::D(){
	glBegin(GL_QUADS);

	glVertex2f(0.4, -0.5);
	glVertex2f(0.3, -0.5);
	glVertex2f(0.3, 0.5);
	glVertex2f(0.4, 0.5);

	glEnd();

	crescent(0.2, 0, 1.0, 1.0);
}

void gloop::glyphs::E(){
	glBegin(GL_QUADS);

	glVertex2f(0.38, -0.5);
	glVertex2f(0.3, -0.5);
	glVertex2f(0.3, 0.5);
	glVertex2f(0.38, 0.5);

	glVertex2f(-0.3, 0.5);
	glVertex2f(0.3, 0.5);
	glVertex2f(0.3, 0.4);
	glVertex2f(-0.3, 0.4);

	glVertex2f(-0.3, -0.05);
	glVertex2f(0.3, -0.05);
	glVertex2f(0.3, 0.05);
	glVertex2f(-0.3, 0.05);

	glVertex2f(-0.3, -0.4);
	glVertex2f(0.3, -0.4);
	glVertex2f(0.3, -0.5);
	glVertex2f(-0.3, -0.5);

	glEnd();
}

void gloop::glyphs::H(){
	glBegin(GL_QUADS);

	glVertex2f(-0.3, -0.05);
	glVertex2f(0.3, -0.05);
	glVertex2f(0.3, 0.1);
	glVertex2f(-0.3, 0.1);

	glVertex2f(-0.3, -0.5);
	glVertex2f(-0.2, -0.5);
	glVertex2f(-0.2, 0.5);
	glVertex2f(-0.3, 0.5);

	glVertex2f(0.3, -0.5);
	glVertex2f(0.2, -0.5);
	glVertex2f(0.2, 0.5);
	glVertex2f(0.3, 0.5);

	glEnd();
}

void gloop::glyphs::I(){
	glBegin(GL_QUADS);

	glVertex2f(-0.05, -0.5);
	glVertex2f(0.05, -0.5);
	glVertex2f(0.05, 0.5);
	glVertex2f(-0.05, 0.5);

	glEnd();
}

void gloop::glyphs::L(){
	glBegin(GL_QUADS);

	glVertex2f(0.5,-0.5);
	glVertex2f(0.4,-0.5);
	glVertex2f(0.4,0.5);
	glVertex2f(0.5,0.5);

	glVertex2f(0.5, -0.5);
	glVertex2f(0, -0.5);
	glVertex2f(0, -0.4);
	glVertex2f(0.5, -0.4);

	glEnd();
}

void gloop::glyphs::N(){
	glBegin(GL_QUADS);

	glVertex2f(-0.3, -0.5);
	glVertex2f(-0.2, -0.5);
	glVertex2f(0.3, 0.5);
	glVertex2f(0.2, 0.5);

	glVertex2f(-0.3, -0.5);
	glVertex2f(-0.2, -0.5);
	glVertex2f(-0.2, 0.5);
	glVertex2f(-0.3, 0.5);

	glVertex2f(0.3, -0.5);
	glVertex2f(0.2, -0.5);
	glVertex2f(0.2, 0.5);
	glVertex2f(0.3, 0.5);

	glEnd();
}

void gloop::glyphs::Y(){
	glBegin(GL_QUADS);

	glVertex2f(-0.5, 0.5);
	glVertex2f(-0.4, 0.5);
	glVertex2f(0.05, -0.5);
	glVertex2f(-0.05,-0.5);

	glVertex2f(-0.3, 0);
	glVertex2f(-0.2, 0);
	glVertex2f(0.3,0.5);
	glVertex2f(0.2, 0.5);

	glEnd();
}

void gloop::glyphs::R(){
	glBegin(GL_QUADS);

	glVertex2f(0.38, -0.5);
	glVertex2f(0.3, -0.5);
	glVertex2f(0.3, 0.5);
	glVertex2f(0.38, 0.5);

	glVertex2f(0.3, 0);
	glVertex2f(0.2, 0);
	glVertex2f(-0.3, -0.5);
	glVertex2f(-0.2, -0.5);

	glEnd();
	crescent(0.2, 0.25, 0.5);
}

void gloop::glyphs::T(){
	glBegin(GL_QUADS);

	glVertex2f(-0.05, -0.5);
	glVertex2f(0.05, -0.5);
	glVertex2f(0.05, 0.5);
	glVertex2f(-0.05, 0.5);

	glVertex2f(-0.3, 0.5);
	glVertex2f(0.3, 0.5);
	glVertex2f(0.3, 0.4);
	glVertex2f(-0.3, 0.4);

	glEnd();
}
