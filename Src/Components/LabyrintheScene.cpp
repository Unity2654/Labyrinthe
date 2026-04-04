#include "LabyrintheScene.h"
#include "../Laby/tab.h"
#include "../Laby3D/Laby3D.h"
#include "../Laby/generation.h"
#include <GL/glut.h>
#include <cmath>

LabyrintheScene::LabyrintheScene()
	:	laby(tab_start(WIDTH, HEIGHT, false), X_SIZE, Z_SIZE, Y_SIZE, WALL_THICKNESS, PILLAR_WIDTH),
		window(480,480,50,50,"Labyrinthe") {
	laby.displayInScene(*this);
}

void LabyrintheScene::display(){
	// Main scene
	window.displayViewPort();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	displayLights();
	displayObjects();
	
	// Minimap
	float map_size = max(window.getSizeX() * (0.1), window.getSizeY() * (0.1));
	glViewport(0, window.getSizeY() - map_size, map_size, map_size);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-15, 15, -15, 15, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		0.0, 30.0, 0.0, // position caméra
		0.0, 0.0, 0.0,  // point regardé
		0.0, 0.0, -1.0);

	displayLights();
	displayObjects();
	glPushMatrix();
	glTranslatef(7.0, 2.0, 5.0);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();

	glutSwapBuffers();
}

void LabyrintheScene::reshape(int wx, int wy){
	window.reshape(wx, wy);
}