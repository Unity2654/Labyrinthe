#pragma once

namespace gloop {
	// Simple data structure made to store some properties of the scene and to apply them
	class SceneProperties {
	private :
		// If true, the textures are enabled in the scene
		bool textures = true;
		// If true, the lights are enabled in the scene
		bool lights = true;

	public : 
		// Toggle the textures
		void toggleTexures();
		// Toggle the lights
		void toggleLights();
		
		// Applies the stored properties to the current scene
		void display();

	};

}