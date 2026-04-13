#include "MenuScene.h"
#include <GL/glut.h>
#include <cmath>
#include "../GlOOPLib/PropertyManager/GlPropertyManager.h"
#include "../Laby3D/Laby3D.h"
#include "../Laby/generation.h"
#include "../Laby3D/Ground.h"
#include "../Laby3D/Wall.h"
#include "MenuElements.h"



MenuScene::MenuScene() : UI(1000,1000) {
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

	auto element = UI.registerElement(gloop::Rectangle::fromCenter({ 500, 500 }, 300, 100));

	StartButton start = StartButton(
		{ POS.x,POS.y, (float)(POS.z + 2) }, 
		0.7, 
		0.2, 
		element
	);
	addObject(start);
	addObject(TitleText({ POS.x,POS.y+0.65f, (float)(POS.z + 2.0f) }));
}

void MenuScene::update(){
	UI.update();
	updateEntities();
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

	glutSwapBuffers();
}
