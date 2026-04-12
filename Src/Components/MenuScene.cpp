#include "MenuScene.h"
#include <GL/glut.h>
#include <cmath>
#include "../GlOOPLib/PropertyManager/GlPropertyManager.h"
#include "../Laby3D/Laby3D.h"
#include "../Laby/generation.h"
#include "../Laby3D/Ground.h"
#include "../Laby3D/Wall.h"
#include "MenuElements.h"



MenuScene::MenuScene(){
	//Laby3D laby{ tab_start(10, 10, false), 30, 30, 4.0, 0.2, 0.4 };
	//laby.displayInScene(*this);
	addObject(Ground(2,50));
	addEntity(MovingWall({1,5.0}, {1.0,0.0}, {1,10.0}, 2, Z_SIZE, WALL_THICKNESS, Y_SIZE, 90));
	addEntity(MovingWall({ -1,5.0 }, { -1,0.0 }, { -1,10.0 }, 2, Z_SIZE, WALL_THICKNESS, Y_SIZE, 90));
}

void MenuScene::display(){
	auto& window = prop::getDisplay();
	// Camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)window.getSizeX() / window.getSizeY(), 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(POS.x, POS.y, POS.z, POS.x, POS.y, POS.z+1.0, 0.0, 1.0, 0.0);

	// Main scene
	window.displayViewPort();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	displayLights();
	displayObjects();

	glTranslatef(0.0, 0.0,3.0);
	glutSolidSphere(0.05, 20, 20);

	glutSwapBuffers();
}
