#include "LabyrintheScene.h"
#include "../Laby/tab.h"
#include "../Laby3D/Laby3D.h"
#include "../Laby/generation.h"
#include <GL/glut.h>
#include <cmath>
#include "../GlOOPLib/PropertyManager/GlPropertyManager.h"
#include "Character.h"

void LabyrintheScene::drawMinimap(gloop::Display& window){
#if defined(WIN32) || defined(WIN32)
	float map_size = max(window.getSizeX() * (0.1), window.getSizeY() * (0.1));
#else
	float map_size = std::max(window.getSizeX() * (0.1), window.getSizeY() * (0.1));
#endif
	auto cpos = player.getPosition();
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
	player.renderOnMap(2.0f);
}

LabyrintheScene::LabyrintheScene()
	:	laby(tab_start(WIDTH, HEIGHT, false), X_SIZE, Z_SIZE, Y_SIZE, WALL_THICKNESS, PILLAR_WIDTH),
	player({1.0f, 1.75f, 1.0f}) {
	laby.displayInScene(*this);
}

const std::vector<gloop::CollisionBox> LabyrintheScene::getNearbyHitboxes(const gloop::Vector3f& position) const
{
	return laby.getMazeCollisionBox();
}

Character& LabyrintheScene::getPlayer(){
	return player;
}

void LabyrintheScene::onLoad(){
	glutSetCursor(GLUT_CURSOR_NONE);
	prop::getMouse().isWarpEnabled = true;
	prop::getKey().registerCallback('c', [this](bool b) {
		if (b)
			getPlayer().switchCamera();
	});
}

void LabyrintheScene::update(){
	player.update();
	Scene::update();
}



void LabyrintheScene::display(){
	prop::getDisplayMode().display();
	prop::getSceneProperties().display();
	auto& window = prop::getDisplay();

	// Main scene
	window.displayViewPort();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	player.render();
	displayLights();
	displayObjects();
	
	// Minimap
	if (player.isFirstPerson())
		drawMinimap(window);

	glutSwapBuffers();
}
