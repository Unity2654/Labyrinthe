#include "LabyrintheScene.h"
#include "../Laby/tab.h"
#include "../Laby3D/Laby3D.h"
#include "../Laby/generation.h"
#include <GL/glut.h>

LabyrintheScene::LabyrintheScene()
	:	laby(tab_start(WIDTH, HEIGHT, false), X_SIZE, Z_SIZE, Y_SIZE, WALL_THICKNESS, PILLAR_WIDTH) {
	laby.displayInScene(*this);
}

void LabyrintheScene::display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Main scene
	displayLights();
	displayObjects();
	// Minimap


	glutSwapBuffers();
}
