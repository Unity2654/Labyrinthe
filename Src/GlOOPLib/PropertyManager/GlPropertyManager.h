#pragma once
#include "Display.h"
#include "../Maths/Rectangle.h"

namespace gloop {
	class GlPropertyManager {
	private:
		static GlPropertyManager* instance;

		//SceneManager
		//Mouse
		Display window;
		static GlPropertyManager& _get();
		GlPropertyManager();

	public :
		void operator=(const GlPropertyManager&) = delete;
		GlPropertyManager(const GlPropertyManager&) = delete;

		static void init(int argc, char** argv, Rectangle windowDimensions, std::string windowName);

		static Display& getDisplay();
	};
}

using prop = gloop::GlPropertyManager;