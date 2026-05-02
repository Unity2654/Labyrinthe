#include "GlPropertyManager.h"
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

namespace gloop {
	GlPropertyManager* GlPropertyManager::instance = nullptr;

	GlPropertyManager& GlPropertyManager::get() {
		if (instance == nullptr)
			instance = new GlPropertyManager();
		return *instance;
	}

	GlPropertyManager::GlPropertyManager() : window(nullptr), sceneManager(nullptr), mouse(nullptr), key(nullptr), dm(nullptr) {}

	void GlPropertyManager::init(int argc, char** argv, Rectangle windowDimensions, std::string windowName) {
		GlPropertyManager& man = get();

		man.window = new Display(windowDimensions, windowName);
		man.sceneManager = new SceneManager();
		man.mouse = new Mouse();
		man.key = new KeybordManager();
		man.dm = new DisplayMode();

		glutInit(&argc, argv);
		man.window->createWindow();
	}

	Display& GlPropertyManager::getDisplay() {
		return *(get().window);
	}

	SceneManager& GlPropertyManager::getSceneManager() {
		return (*get().sceneManager);
	}

	Mouse& GlPropertyManager::getMouse() {
		return (*get().mouse);
	}

	DisplayMode& GlPropertyManager::getDisplayMode(){
		return (*get().dm);
	}

	KeybordManager& GlPropertyManager::getKey() {
		return (*get().key);
	}

	GlPropertyManager::~GlPropertyManager() {
		if (window != nullptr)
			delete window;
		if (sceneManager != nullptr)
			delete sceneManager;
		if (mouse != nullptr)
			delete mouse;
		if (key != nullptr)
			delete key;
		if (dm != nullptr)
			delete dm;
	}

	void DisplayMode::next() {
		currentDisplay = (currentDisplay + 1) % displayCount;
	}

	void DisplayMode::display() {
		glPolygonMode(GL_FRONT, displays[currentDisplay]);
	}
}