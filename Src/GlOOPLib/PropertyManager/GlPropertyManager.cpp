#include "GlPropertyManager.h"
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

gloop::GlPropertyManager* gloop::GlPropertyManager::instance = nullptr;

gloop::GlPropertyManager& gloop::GlPropertyManager::get(){
	if (instance == nullptr)
		instance = new GlPropertyManager();
	return *instance;
}

gloop::GlPropertyManager::GlPropertyManager() : window(nullptr), sceneManager(nullptr), mouse(nullptr) {}

void gloop::GlPropertyManager::init(int argc, char** argv, Rectangle windowDimensions, std::string windowName){
	GlPropertyManager& man = get();

	man.window = new Display(windowDimensions, windowName);
	man.sceneManager = new SceneManager();
	man.mouse = new Mouse();
	man.key = new KeybordManager();

	glutInit(&argc, argv);
	man.window->createWindow();
}

gloop::Display& gloop::GlPropertyManager::getDisplay(){
	return *(get().window);
}

gloop::SceneManager& gloop::GlPropertyManager::getSceneManager(){
	return (*get().sceneManager);
}

gloop::Mouse& gloop::GlPropertyManager::getMouse(){
	return (*get().mouse);
}

gloop::KeybordManager& gloop::GlPropertyManager::getKey(){
	return (*get().key);
}

gloop::GlPropertyManager::~GlPropertyManager(){
	if(window != nullptr)
		delete window;
	if (sceneManager != nullptr)
		delete sceneManager;
	if (mouse != nullptr)
		delete mouse;
	if (key != nullptr)
		delete key;
}
