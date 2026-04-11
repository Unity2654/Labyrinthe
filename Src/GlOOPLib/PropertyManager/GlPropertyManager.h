#pragma once
#include "Display.h"
#include "../Maths/Rectangle.h"
#include "SceneManager.h"
#include "Mouse.h"

/* Class made to allow to manage general properties of the application, and allow their access from a static context.
   The class mostly contains static methods, and implements the Singleton design pattern.
*/
namespace gloop {
	class GlPropertyManager {
	private:
		static GlPropertyManager* instance;

		Mouse* mouse;
		SceneManager* sceneManager;
		Display* window;
		static inline GlPropertyManager& get();
		GlPropertyManager();

	public :
		void operator=(const GlPropertyManager&) = delete;
		GlPropertyManager(const GlPropertyManager&) = delete;

		static void init(int argc, char** argv, Rectangle windowDimensions, std::string windowName);

		static Display& getDisplay();
		static SceneManager& getSceneManager();
		static Mouse& getMouse();

		~GlPropertyManager();
	};
}

using prop = gloop::GlPropertyManager;