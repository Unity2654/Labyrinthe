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
		const constexpr static int FPS = 60;
		bool mainScene = false; // TODO : Remove this once the main scene works properly
		
		void operator=(const GlPropertyManager&) = delete;
		GlPropertyManager(const GlPropertyManager&) = delete;

		static void init(int argc, char** argv, Rectangle windowDimensions, std::string windowName);

		static Display& getDisplay();
		static SceneManager& getSceneManager();
		static Mouse& getMouse();
		static bool isMainScene() { return get().mainScene; } // TODO : This as well
		static void setMainScene() { get().mainScene = true; } // TODO : This as well

		~GlPropertyManager();
	};
}

using prop = gloop::GlPropertyManager;