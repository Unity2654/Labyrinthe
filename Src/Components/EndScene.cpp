#include "EndScene.h"
#include "../Laby3D/EndDoor.h"
#include "../Laby3D/Ground.h"
#include "MenuElements.h"
#include "../GlOOPLib/PropertyManager/GlPropertyManager.h"
#include "GL/gl.h"
#include "GL/glu.h"
#include "GL/glut.h"

EndScene::EndScene() : UI(1000,1000) {
    // addObject(Ground(3,50));

    addObject(EndDoor(POS.x, POS.z + 3.0f, 2.5f, 1.5f, 180.0f, *this));
	addObject(Wall(POS.x, POS.z + 3.0f, 5.0f, 0.2f, 4.0f, 180.0f));
	addStaticLight(light);



    auto element = UI.registerElement(gloop::Rectangle::fromCenter({ 500, 500 }, 300, 100));

    EndButton endButton = EndButton(
        { POS.x,POS.y, (float)(POS.z + 2) }, 
        0.7, 
        0.2, 
        element
    );
    addEntity(endButton);
    addObject(TitleText({ POS.x,POS.y+0.65f, (float)(POS.z + 2.0f) }));
}


void EndScene::update(){
	UI.update();
	updateEntities();
}

void EndScene::display(){
	prop::getDisplayMode().display();
	prop::getSceneProperties().display();
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

void EndScene::onLoad(){
	glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
	prop::getMouse().isWarpEnabled = false;
}