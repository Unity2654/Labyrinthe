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
	addObject(Ground(3,50));

	int nbWalls = (finalPosition - initialPosition).norm() / Z_SIZE;
	auto wallOffset = (finalPosition - initialPosition) / nbWalls;
	gloop::Vector2f pillarOffset = { 0.0, Z_SIZE / 2 };
	addStaticLight(light);

	for (int i = 0; i < nbWalls; i++) {
		auto wallpos = initialPosition + wallOffset * i;
		auto pillarpos = initialPosition + wallOffset * i + pillarOffset;
		addEntity(MovingWall(wallpos, initialPosition, finalPosition, 4, Z_SIZE, WALL_THICKNESS, Y_SIZE, 90));
		addEntity(MovingPillar(pillarpos, initialPosition, finalPosition, 4, PILLAR_WIDTH, Y_SIZE));

		addEntity(MovingWall(wallpos * symmetryFactor, initialPosition * symmetryFactor, finalPosition * symmetryFactor, 4, Z_SIZE, WALL_THICKNESS, Y_SIZE, 90));
		addEntity(MovingPillar(pillarpos * symmetryFactor, initialPosition * symmetryFactor, finalPosition * symmetryFactor, 4, PILLAR_WIDTH, Y_SIZE));
	}
}

void MenuScene::display(){
	auto& window = prop::getDisplay();
	// Camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)window.getSizeX() / window.getSizeY(), 0.1, 17.5);
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
