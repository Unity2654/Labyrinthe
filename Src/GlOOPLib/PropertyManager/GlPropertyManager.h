#pragma once
#include "Display.h"
#include "../Maths/Rectangle.h"
#include "SceneManager.h"
#include "Mouse.h"
#include "../KeybordManager/KeybordManager.h"
#include "SceneProperties.h"

namespace gloop {
	// Data structure storing the current polygon mode of the scene
	class DisplayMode {
	private:
		// Available display modes
		const GLenum displays[3] = { GL_LINE, GL_FILL, GL_POINT };
		// Number of available display modes
		static constexpr int displayCount = 3;
		// Current mode being displayed
		int currentDisplay = 1;
		
	public:
		// Switch for the next display mode
		void next();
		// Enables the current display mode for the scene
		void display();
	};

	// Class made to allow to manage general properties of the application, and allow their access from a static context.
	// The class mostly contains static methods, and implements the Singleton design pattern.
	class GlPropertyManager {
	private:
		// Unique instance of the GlPropertyManager object
		static GlPropertyManager* instance;

		// Unique instances of the properties handled by the GlPropertyManager
		Mouse* mouse;
		SceneManager* sceneManager;
		Display* window;
		KeyboardManager* key;
		DisplayMode* dm;
		SceneProperties* sp;

		// Number of facets in the scene
		int facets = 10;

		// Returns the instance of the GlPropertyManager
		static inline GlPropertyManager& get();
		GlPropertyManager();
	public :
		// Number of display refreshes per seconds in an optimal setup
		const constexpr static int FPS = 60;
		
		void operator=(const GlPropertyManager&) = delete;
		GlPropertyManager(const GlPropertyManager&) = delete;

		// Initialize the properties of the manager
		static void init(int argc, char** argv, Rectangle windowDimensions, std::string windowName);

		// Getters for the various properties handled by the manager
		static Display& getDisplay();
		static SceneManager& getSceneManager();
		static KeyboardManager& getKey();
		static Mouse& getMouse();
		static DisplayMode& getDisplayMode();
		static SceneProperties& getSceneProperties();

		static int getFacets();
		static void increaseFacets();
		static void decreaseFacets();
		
		// Frees the memory used by the manager
		static void destroy();
	};
}

using prop = gloop::GlPropertyManager;