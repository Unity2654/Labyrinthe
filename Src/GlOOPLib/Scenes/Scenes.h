#pragma once
#include <vector>
#include <memory>
#include "../Objects/Object3D.h"
#include "../Objects/Entity3D.h"
#include "../Lights/Lights.h"

namespace gloop {

	 // Inner representation of a Scene.
	 // A scene can contain object, as well as entities, that can be displayed and updated through the execution
	 // The objects are displayed before the scenes.
	class Scene {
	private :
		// Static objects of the scene
		std::vector<std::shared_ptr<Object3D>> objects;
		// Entities of the scene
		std::vector<std::shared_ptr<Entity3D>> entities;
		// Static lights of the scene
		std::vector<std::shared_ptr<Light>> staticLights;
		// Dynamic lights of the scene
		std::vector<std::shared_ptr<Light>> dynamicLights;

	public:
		// Constructors 
		Scene();

		/// Methods
		// Updates all the entities of the scene
		virtual void update();
		// Displays all the objects and entities of the scene
		virtual void display();
		// Called by the scene manager when the current scene is changed to be this one
		virtual void onLoad() {}
		// Called by the scene manager when this scene is popped or swapped
		virtual void onDeLoad() {}

		// Adds objects to the scene
		template<typename T>
		void addObject(T o) {
			objects.push_back(std::make_shared<T>(o));
		}

		// Adds entities to the scene
		template<typename T>
		void addEntity(T e) {
			entities.push_back(std::make_shared<T>(e));
		}

		
		// Adds lighting to the scene
		// Static lights are not updated.
		template<typename T>
		void addStaticLight(T l) {
			staticLights.push_back(std::make_shared<T>(l));
		}
		
		// Adds lighting to the scene
		// Dynamic lights are updated every frame.
		template<typename T>
		void addDynamicLight(T l) {
			dynamicLights.push_back(std::make_shared<T>(l));
		}

	protected:
		// Display methods that can be used by inherited classes to display lights and objects at will
		void displayLights();
		void displayObjects();

		// Update methods that can be used by inherited classes to update entities and dynamic lights
		void updateLights();
		void updateEntities();

	};
}
