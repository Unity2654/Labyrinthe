#include "Text.h"
#include <GL/gl.h>
#include <corecrt_math_defines.h>
#include <cmath>
#include "../Lights/Materials.h"
#include <iostream>

void crescent() {
	float angle = M_PI;
	float target = angle + M_PI;
	float scale = 0.5f;
	float step = 0.5f;
	float fullness = 0.8f;
	glBegin(GL_TRIANGLE_STRIP);
	while (angle < target) {
		glVertex2f(scale * sinf(angle), scale * cosf(angle));
		glVertex2f(fullness * scale * sinf(angle), scale * cosf(angle));
		angle += step;
	}
	glEnd();
}

void gloop::glyphs::A(){
	glBegin(GL_QUADS);
	
	glVertex2f(0.1,0.0);
	glVertex2f(0.1,0.2);
	glVertex2f(0.5,1.0);
	glVertex2f(0.5,0.8);

	glVertex2f(0.9, 0.0);
	glVertex2f(0.9, 0.2);
	glVertex2f(0.5, 1.0);
	glVertex2f(0.5, 0.8);

	glVertex2f(0.3, 0.5);
	glVertex2f(0.7, 0.5);
	glVertex2f(0.7, 0.4);
	glVertex2f(0.3, 0.4);

	glEnd();
}

void gloop::glyphs::B(){
	glBegin(GL_QUADS);
	
	glVertex2f(0.4, -0.5);
	glVertex2f(0.3, -0.5);
	glVertex2f(0.3, 0.5);
	glVertex2f(0.4, 0.5);

	glEnd();

	crescent();

	/*

	float firstcurve[4][3]= { 
		{ 0.3, -0.5, 0 },
		{ -0.3, -0.5, 0 },
		{ -0.3, 0, 0 },
		{ 0.3, 0, 0.0 } 
	};
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &firstcurve[0][0]);
	glEnable(GL_MAP1_VERTEX_3);
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 30; i++)
		glEvalCoord1f((GLfloat)i / 30.0);
	glEnd();

	float secondcurve[4][3] = {
		{ 0.3, 0, 0 },
		{ -0.3, 0, 0 },
		{ -0.3, 0.5, 0 },
		{ 0.3, 0.5, 0.0 }
	};
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &secondcurve[0][0]);
	glEnable(GL_MAP1_VERTEX_3);
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 30; i++)
		glEvalCoord1f((GLfloat)i / 30.0);
	glEnd();*/
}
