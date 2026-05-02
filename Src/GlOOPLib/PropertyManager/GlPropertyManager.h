#pragma once
#include "Display.h"
#include "../Maths/Rectangle.h"
#include "SceneManager.h"
#include "Mouse.h"
#include "../KeybordManager/KeybordManager.h"
#include "SceneProperties.h"

/* Class made to allow to manage general properties of the application, and allow their access from a static context.
   The class mostly contains static methods, and implements the Singleton design pattern.
*/
namespace gloop {
	class DisplayMode {
	private:
		const GLenum displays[3] = { GL_LINE, GL_FILL, GL_POINT };
		static constexpr int displayCount = 3;
		int currentDisplay = 1;

	public:
		void next();
		void display();
	};

	class GlPropertyManager {
	private:
		static GlPropertyManager* instance;

		Mouse* mouse;
		SceneManager* sceneManager;
		Display* window;
		KeybordManager* key;
		DisplayMode* dm;
		SceneProperties* sp;

		static inline GlPropertyManager& get();
		GlPropertyManager();
	public :
		const constexpr static int FPS = 60;
		
		void operator=(const GlPropertyManager&) = delete;
		GlPropertyManager(const GlPropertyManager&) = delete;

		static void init(int argc, char** argv, Rectangle windowDimensions, std::string windowName);

		static Display& getDisplay();
		static SceneManager& getSceneManager();
		static KeybordManager& getKey();
		static Mouse& getMouse();
		static DisplayMode& getDisplayMode();
		static SceneProperties& getSceneProperties();

		~GlPropertyManager();
	};
}

using prop = gloop::GlPropertyManager;