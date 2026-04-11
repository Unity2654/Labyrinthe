#include "MenuScene.h"
#include <GL/glut.h>
#include <cmath>
#include "../GlOOPLib/PropertyManager/GlPropertyManager.h"
#include "../Laby3D/Laby3D.h"
#include "../Laby/generation.h"

MenuScene::MenuScene(){
	Laby3D laby{ tab_start(10, 10, false), 30, 30, 4.0, 0.2, 0.4 };
	laby.displayInScene(*this);
}

void MenuScene::display(){
	auto& window = prop::getDisplay();
	// Camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)window.getSizeX() / window.getSizeY(), 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 0, 0,0,10, 0.0, 1.0, 0.0);
	std::cout << "d " << std::endl;

	// Main scene
	window.displayViewPort();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	displayLights();
	displayObjects();

	glutSwapBuffers();
}
