#pragma once

namespace gloop {
	class SceneProperties {
	private :
		bool textures = true;
		bool lights = true;

	public : 

		void toggleTexures();
		void toggleLights();

		void display();

	};

}