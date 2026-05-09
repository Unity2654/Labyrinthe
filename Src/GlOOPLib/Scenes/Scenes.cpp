#include "Scenes.h"
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

namespace gloop
{
	Scene::Scene() {}

	void Scene::update(){
		updateLights();
		updateEntities();
	}

	void Scene::display(){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		displayLights();
		displayObjects();
		glFlush();
		glutSwapBuffers();
	}

	void Scene::displayLights(){
		// Displaying the lights to the scene
		for (std::shared_ptr<Light>& l : staticLights)
		{
			l->render();
		}
		for (std::shared_ptr<Light>& l : dynamicLights)
		{
			l->render();
		}
	}

	void Scene::displayObjects(){
		// Displaying the content of the scene
		for (std::shared_ptr<Object3D>& o : objects)
		{
			o->render();
		}
		for (std::shared_ptr<Entity3D>& e : entities)
		{
			e->render();
		}
	}

	void Scene::updateLights(){
		std::cout << "Updating lights" << std::endl;
		// Updating every lights of the scene
		for (std::shared_ptr<Light>& l : dynamicLights)
		{
			std::cout << "Updating lights" << l.get()->data.diffuseColor.r << std::endl;

			l->update();
		}
	}

	void Scene::updateEntities(){
		// Updating every entity in the scene
		for (std::shared_ptr<Entity3D>& e : entities)
		{
			e->update();
		}
	}
}
