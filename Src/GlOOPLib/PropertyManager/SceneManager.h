#pragma once
#include <stack>
#include <memory>
#include "../Scenes/Scenes.h"

/* Class to allow to manage multiple scenes based on a stack principle
*  If the manager is paused, the current scene won't be updated.
*  Some methods are implemented in the header due to the use of templates
*/
namespace gloop {
	class SceneManager {
	private :
		std::stack<std::unique_ptr<Scene>> scenes;
		bool paused = false;

	public :
		SceneManager() = default;
		
		// Add/Remove scenes

		/* Adds a scene on the top of the stack */
		template<typename S>
		void pushScene(S scene) {
			scenes.push(std::make_unique<Scene>(scene));
		}

		/* Remove the scene on the top of the stack */
		void popScene();

		// Active scene of the manager

		/* Returns the scene at the top of the stack */
		template<typename S>
		S& getActiveScene() {
			return std::dynamic_cast<S>(*(scenes.top()));
		}

		template<>
		Scene& getActiveScene<Scene>() {
			return *scenes.top();
		}

		// Status of the manager
		bool isPaused() const;
		void pause();
		void unPause();
		bool togglePause();

		// Update/display methods
		void display() const;
		void update();

	};
}