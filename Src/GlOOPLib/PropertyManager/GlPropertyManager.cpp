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

	GlPropertyManager::GlPropertyManager() : window(nullptr), sceneManager(nullptr), mouse(nullptr), key(nullptr), dm(nullptr), sp(nullptr) {}

	void GlPropertyManager::init(int argc, char** argv, Rectangle windowDimensions, std::string windowName) {
		GlPropertyManager& man = get();

		man.window = new Display(windowDimensions, windowName);
		man.sceneManager = new SceneManager();
		man.mouse = new Mouse();
		man.key = new KeybordManager();
		man.dm = new DisplayMode();
		man.sp = new SceneProperties();

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

	SceneProperties& GlPropertyManager::getSceneProperties(){
		return (*get().sp);
	}

	void GlPropertyManager::destroy()
	{
		GlPropertyManager& instance = get();
		if (instance.window != nullptr) {
			delete instance.window;
			instance.window = nullptr;
		}
		if (instance.sceneManager != nullptr) {
			delete instance.sceneManager;
			instance.sceneManager = nullptr;
		}
		if (instance.mouse != nullptr) {
			delete instance.mouse;
			instance.mouse = nullptr;
		}
		if (instance.key != nullptr) {
			delete instance.key;
			instance.key = nullptr;
		}
		if (instance.dm != nullptr) {
			delete instance.dm;
			instance.dm = nullptr;
		}
		if (instance.sp != nullptr) {
			delete instance.sp;
			instance.sp = nullptr;
		}
	}

	KeybordManager& GlPropertyManager::getKey() {
		return (*get().key);
	}

	void DisplayMode::next() {
		currentDisplay = (currentDisplay + 1) % displayCount;
	}

	void DisplayMode::display() {
		glPolygonMode(GL_FRONT, displays[currentDisplay]);
	}
}