#include "Scenes.h"
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

namespace gloop {
	Scene::Scene(){}

	void Scene::update(){
		doUpdate();
		// Updating every lights of the scene
		for (std::unique_ptr<Light>& l : dynamicLights) {
			l->update();
		}
		// Updating every entity in the scene
		for (std::unique_ptr<Entity3D>& e : entities) {
			e->update();
		}
	}

	void Scene::display(){
		doDisplay();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Displaying the lights to the scene
		for (std::unique_ptr<Light>& l : staticLights) {
			l->render();
		}
		for (std::unique_ptr<Light>& l : dynamicLights) {
			l->render();
		}
		// Displaying the content of the scene
		for (std::unique_ptr<Object3D>& o : objects) {
			o->render();
		}
		for (std::unique_ptr<Entity3D>& e : entities) {
			e->render();
		}
		glFlush();
		glutSwapBuffers();
	}
}
