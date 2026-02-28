#include "Scenes.h"

namespace gloop {
	Scene::Scene(){}

	Scene::Scene(std::vector<Object3D> objs) :
		objects(objs){}

	Scene::Scene(std::vector<Object3D> objs, std::vector<Entity3D> ents):
		objects(objs),
		entities(ents){}

	void Scene::update(){
		// Updating every entity in the scene
		for (Entity3D& e : entities) {
			e.update();
		}
	}

	void Scene::display(){
		// Displaying the content of the scene
		for (Object3D& o : objects) {
			o.render();
		}
		for (Entity3D& e : entities) {
			e.render();
		}
	}

	void Scene::addObject(Object3D o){
		objects.push_back(o);
	}

	void Scene::addObjects(std::vector<Object3D> objs){
		for (Object3D& o : objs) {
			objects.push_back(o);
		}
	}

	void Scene::addEntity(Entity3D e){
		entities.push_back(e);
	}

	void Scene::addEntities(std::vector<Entity3D> ents){
		for (Entity3D& e : ents) {
			entities.push_back(e);
		}
	}
}
