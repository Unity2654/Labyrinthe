#include "GlPropertyManager.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

gloop::GlPropertyManager* gloop::GlPropertyManager::instance = nullptr;

gloop::GlPropertyManager& gloop::GlPropertyManager::get(){
	if (instance == nullptr)
		instance = new GlPropertyManager();
	return *instance;
}

gloop::GlPropertyManager::GlPropertyManager() : window(nullptr) {}

void gloop::GlPropertyManager::init(int argc, char** argv, Rectangle windowDimensions, std::string windowName){
	GlPropertyManager& man = get();

	man.window = new Display(windowDimensions, windowName);
	glutInit(&argc, argv);
	man.window->createWindow();
}

gloop::Display& gloop::GlPropertyManager::getDisplay(){
	return *(get().window);
}

gloop::GlPropertyManager::~GlPropertyManager(){
	if(window != nullptr)
		delete window;
}
