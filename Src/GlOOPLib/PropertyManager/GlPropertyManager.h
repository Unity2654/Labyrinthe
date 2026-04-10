#pragma once
#include "Display.h"
#include "../Maths/Rectangle.h"

namespace gloop {
	class GlPropertyManager {
	private:
		//SceneManager
		//Mouse
		static Display window;

	public :

		static void init(int argc, char** argv, Rectangle windowDimensions, std::string windowName);

		static Display& getDisplay() {
			return window;
		}

	};
}

using prop = gloop::GlPropertyManager;