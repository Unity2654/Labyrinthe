#include "LabyrintheScene.h"
#include "../Laby/tab.h"
#include "../Laby3D/Laby3D.h"
#include "../Laby/generation.h"
#include <GL/glut.h>
#include <cmath>
#include "../GlOOPLib/PropertyManager/GlPropertyManager.h"
#include "Character.h"

LabyrintheScene::LabyrintheScene()
	:	laby(tab_start(WIDTH, HEIGHT, false), X_SIZE, Z_SIZE, Y_SIZE, WALL_THICKNESS, PILLAR_WIDTH),
	player({1.0f, 1.75f, 1.0f}) {
	laby.displayInScene(*this);
}

const std::vector<gloop::CollisionBox> LabyrintheScene::getNearbyHitboxes(const gloop::Vector3f& position) const
{
	return laby.getMazeCollisionBox();
}

void LabyrintheScene::onLoad(){
	glutSetCursor(GLUT_CURSOR_NONE);
	prop::getMouse().isWarpEnabled = true;
}

void LabyrintheScene::update(){
	player.update();
	Scene::update();
}

void LabyrintheScene::display(){
	prop::getDisplayMode().display();
	auto& window = prop::getDisplay();

	// Main scene
	window.displayViewPort();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	player.render();
	displayLights();
	displayObjects();
	
	// Minimap
	float map_size = max(window.getSizeX() * (0.1), window.getSizeY() * (0.1));
	auto& cpos = player.getPosition();
	glViewport(0, window.getSizeY() - map_size, map_size, map_size);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-15, 15, -15, 15, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		cpos.x, 30.0, cpos.z, // position caméra
		cpos.x, 0.0, cpos.z,  // point regardé
		0.0, 0.0, -1.0);

	displayLights();
	displayObjects();
	glPushMatrix();
	glTranslatef(cpos.x, 2.0, cpos.z);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();

	glutSwapBuffers();
}