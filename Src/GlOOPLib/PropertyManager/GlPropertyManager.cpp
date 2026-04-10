#include "GlPropertyManager.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

gloop::GlPropertyManager& gloop::GlPropertyManager::_get(){
	if (instance == nullptr)
		instance = new GlPropertyManager();
	return *instance;
}

void gloop::GlPropertyManager::init(int argc, char** argv, Rectangle windowDimensions, std::string windowName){
	GlPropertyManager& man = _get();

	man.window = Display(windowDimensions, windowName);
	glutInit(&argc, argv);
	man.window.createWindow();
}

gloop::Display& gloop::GlPropertyManager::getDisplay(){
	return _get().window;
}
