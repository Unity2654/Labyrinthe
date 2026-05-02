#pragma once

namespace gloop {
	class SceneProperties {
	private :
		bool textures;
		bool lights;

	public : 

		void toggleTexures();
		void toggleLights();

		void display();

	};

}