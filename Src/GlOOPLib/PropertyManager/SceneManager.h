#pragma once
#include <stack>
#include <memory>
#include "../Scenes/Scenes.h"

// Class to allow to manage multiple scenes based on a stack principle
//  If the manager is paused, the current scene won't be updated.
//  Some methods are implemented in the header due to the use of templates
// 
// Only the main active scene is updated
//
namespace gloop {
	class SceneManager {
	private :
		// Scenes currently stored in the manager
		std::stack<std::shared_ptr<Scene>> scenes;
		// If true, the top scene of the stack is not updated
		bool paused = false;

	public :
		SceneManager() = default;
		
		// Add/Remove scenes

		// Adds a scene on the top of the stack
		template<typename S>
		void pushScene(S& scene) {
			scenes.push(std::make_shared<S>(scene));
			scenes.top()->onLoad();
		}

		// Remove the scene on the top of the stack
		void popScene();

		// Active scene of the manager

		// Returns the scene at the top of the stack
		template<typename S>
		S& getActiveScene() {
			return static_cast<S>(*(scenes.top()));
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