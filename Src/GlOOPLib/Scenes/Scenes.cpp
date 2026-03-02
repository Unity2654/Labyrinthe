#include "Scenes.h"
#include <iostream>

namespace gloop {
	Scene::Scene(){}

	void Scene::update(){
		doUpdate();
		// Updating every entity in the scene
		for (std::unique_ptr<Entity3D>& e : entities) {
			e->update();
		}
	}

	void Scene::display(){
		doDisplay();
		// Displaying the content of the scene
		for (std::unique_ptr<Object3D>& o : objects) {
			o->render();
		}
		for (std::unique_ptr<Entity3D>& e : entities) {
			e->render();
		}
	}
}
