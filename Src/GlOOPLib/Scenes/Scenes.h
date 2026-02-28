#pragma once
#include <vector>
#include "../Objects/Object3D.h"
#include "../Objects/Entity3D.h"


namespace gloop {

	/**
	 * Inner representation of a Scene.
	 * A scene can contain object, as well as entities, that can be displayed and updated through the execution
	 * The objects are displayed before the scenes.
	 */
	class Scene {
	private :
		std::vector<Object3D> objects;
		std::vector<Entity3D> entities;
	public:
		// Constructors 
		Scene();
		Scene(std::vector<Object3D> objs);
		Scene(std::vector<Object3D> objs, std::vector<Entity3D> ents);

		/// Methods
		// Updates all the entities of the scene
		void update();
		// Displays all the objects and entities of the scene
		void display();

		// Function triggered at the start of the call of the update method
		virtual void doUpdate() = 0;
		// Function triggered at the start of the call of the display method
		virtual void doDisplay() = 0;

		// Adds objects to the scene
		void addObject(Object3D o);
		void addObjects(std::vector<Object3D> objs);

		// Adds entities to the scene
		void addEntity(Entity3D e);
		void addEntities(std::vector<Entity3D> ents);
	};
}