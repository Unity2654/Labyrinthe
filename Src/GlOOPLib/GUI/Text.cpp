#include "Text.h"
#include <GL/gl.h>
#include <cmath>
#include "../Lights/Materials.h"
#include <iostream>
#if defined(WIN32) || defined(WIN32)
#define M_PI 3.14159f
#endif


void crescent(float px, float py, float scale, float rotation = 1.0) {
	glPushMatrix();
	glTranslatef(px, py, 0);

	float target = M_PI;
	float angle = target + M_PI;
	scale = 0.5f * scale * rotation;
	float step = 0.1f;
	float fullness = 0.6f;
	glBegin(GL_TRIANGLE_STRIP);
	while (angle > target) {
		glVertex2f(scale * sinf(angle), scale * cosf(angle));
		glVertex2f(fullness * scale * sinf(angle), scale * cosf(angle));
		angle -= step;
	}
	glEnd();

	glPopMatrix();
}

void gloop::glyphs::A(){
	glBegin(GL_QUADS);
	
	glVertex2f(0.5f,-0.5f);
	glVertex2f(0.4f,-0.5f);
	glVertex2f(0.0f,0.3f);
	glVertex2f(0.0f,0.5f);

	glVertex2f(0.0f, 0.5f);
	glVertex2f(0.0f, 0.3f);
	glVertex2f(-0.4f, -0.5f);
	glVertex2f(-0.5f, -0.5f);

	glVertex2f(-0.3f, 0.0f);
	glVertex2f(0.3f, 0.0f);
	glVertex2f(0.3f, -0.1f);
	glVertex2f(-0.3f, -0.1f);

	glEnd();
}

void gloop::glyphs::B(){

	glBegin(GL_QUADS);

	glVertex2f(0.18f, -0.5f);
	glVertex2f(0.1f, -0.5f);
	glVertex2f(0.1f, 0.5f);
	glVertex2f(0.18f, 0.5f);

	glEnd();

	crescent(0,-0.25f,0.5f);
	crescent(0, 0.25f, 0.5f);
}

void gloop::glyphs::C(){
	crescent(0, 0, 1.0f, -1.0f);
}

void gloop::glyphs::D(){
	glBegin(GL_QUADS);

	glVertex2f(0.4f, -0.5f);
	glVertex2f(0.3f, -0.5f);
	glVertex2f(0.3f, 0.5f);
	glVertex2f(0.4f, 0.5f);

	glEnd();

	crescent(0.2f, 0, 1.0f, 1.0f);
}

void gloop::glyphs::E(){
	glBegin(GL_QUADS);

	glVertex2f(0.38f, -0.5f);
	glVertex2f(0.3f, -0.5f);
	glVertex2f(0.3f, 0.5f);
	glVertex2f(0.38f, 0.5f);

	glVertex2f(-0.3f, 0.5f);
	glVertex2f(0.3f, 0.5f);
	glVertex2f(0.3f, 0.4f);
	glVertex2f(-0.3f, 0.4f);

	glVertex2f(-0.3f, 0.05f);
	glVertex2f(0.3f, 0.05f);
	glVertex2f(0.3f, -0.05f);
	glVertex2f(-0.3f, -0.05f);

	glVertex2f(-0.3f, -0.4f);
	glVertex2f(0.3f, -0.4f);
	glVertex2f(0.3f, -0.5f);
	glVertex2f(-0.3f, -0.5f);

	glEnd();
}

void gloop::glyphs::H(){
	glBegin(GL_QUADS);

	glVertex2f(-0.3f, 0.05f);
	glVertex2f(0.3f, 0.05f);
	glVertex2f(0.3f, -0.05f);
	glVertex2f(-0.3f, -0.05f);

	glVertex2f(-0.3f, 0.5f);
	glVertex2f(-0.2f, 0.5f);
	glVertex2f(-0.2f, -0.5f);
	glVertex2f(-0.3f, -0.5f);

	glVertex2f(0.3f, -0.5f);
	glVertex2f(0.2f, -0.5f);
	glVertex2f(0.2f, 0.5f);
	glVertex2f(0.3f, 0.5f);

	glEnd();
}

void gloop::glyphs::I(){
	glBegin(GL_QUADS);

	glVertex2f(-0.05f, 0.5f);
	glVertex2f(0.05f, 0.5f);
	glVertex2f(0.05f, -0.5f);
	glVertex2f(-0.05f, -0.5f);
	
	glEnd();
}

void gloop::glyphs::L(){
	glBegin(GL_QUADS);

	glVertex2f(0.5f,-0.5f);
	glVertex2f(0.4f,-0.5f);
	glVertex2f(0.4f,0.5f);
	glVertex2f(0.5f,0.5f);

	glVertex2f(0.5f, -0.5f);
	glVertex2f(0, -0.5f);
	glVertex2f(0, -0.4f);
	glVertex2f(0.5f, -0.4f);

	glEnd();
}

void gloop::glyphs::N(){
	glBegin(GL_QUADS);

	glVertex2f(0.2f, 0.5f);
	glVertex2f(0.3f, 0.5f);
	glVertex2f(-0.2f, -0.5f);
	glVertex2f(-0.3f, -0.5f);

	glVertex2f(-0.3f, 0.5f);
	glVertex2f(-0.2f, 0.5f);
	glVertex2f(-0.2f, -0.5f);
	glVertex2f(-0.3f, -0.5f);

	glVertex2f(0.3f, -0.5f);
	glVertex2f(0.2f, -0.5f);
	glVertex2f(0.2f, 0.5f);
	glVertex2f(0.3f, 0.5f);

	glEnd();
}

void gloop::glyphs::Y(){
	glBegin(GL_QUADS);

	glVertex2f(-0.4f, 0.5f);
	glVertex2f(-0.3f, 0.5f);
	glVertex2f(0.15f, -0.5f);
	glVertex2f(0.05f,-0.5f);

	glVertex2f(0.3f, 0.5f);
	glVertex2f(0.4f, 0.5f);
	glVertex2f(-0.1f, 0);
	glVertex2f(-0.2f, 0);

	glEnd();
}

void gloop::glyphs::R(){

	glBegin(GL_QUADS);

	glVertex2f(0.18f, -0.5f);
	glVertex2f(0.1f, -0.5f);
	glVertex2f(0.1f, 0.5f);
	glVertex2f(0.18f, 0.5f);

	glVertex2f(-0.4f, -0.5f);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.0f, 0);
	glVertex2f(0.1f, 0);

	glEnd();
	crescent(0.0f, 0.25f, 0.5f);
}

void gloop::glyphs::S(){
	crescent(0, -0.25f, 0.5f);
	crescent(0, 0.25f, 0.5f,-1);
}

void gloop::glyphs::T(){
	glBegin(GL_QUADS);

	glVertex2f(-0.05f, 0.5f);
	glVertex2f(0.05f, 0.5f);
	glVertex2f(0.05f, -0.5f);
	glVertex2f(-0.05f, -0.5f);
	
	glVertex2f(-0.3f, 0.5f);
	glVertex2f(0.3f, 0.5f);
	glVertex2f(0.3f, 0.4f);
	glVertex2f(-0.3f, 0.4f);

	glEnd();
}


