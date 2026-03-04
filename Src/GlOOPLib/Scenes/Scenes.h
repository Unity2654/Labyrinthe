#pragma once
#include <vector>
#include <memory>
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
		std::vector<std::unique_ptr<Object3D>> objects;
		std::vector<std::unique_ptr<Entity3D>> entities;
	public:
		// Constructors 
		Scene();

		/// Methods
		// Updates all the entities of the scene
		void update();
		// Displays all the objects and entities of the scene
		void display();

		// Function triggered at the start of the call of the update method
		virtual void doUpdate() {};
		// Function triggered at the start of the call of the display method
		virtual void doDisplay() {};

		// Adds objects to the scene
		template<typename T>
		void addObject(T o) {
			objects.push_back(std::make_unique<T>(o));
		}

		// Adds entities to the scene
		template<typename T>
		void addEntity(T e) {
			entities.push_back(std::make_unique<T>(e));
		}
	};
}
