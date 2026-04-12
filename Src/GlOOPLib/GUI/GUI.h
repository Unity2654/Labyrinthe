#pragma once
#include <vector>
#include "GUIElement.h"

namespace gloop {

	// A graphical user interface.
	// Once updated, it checks the mouse position and state and updates the registered (enabled) GUI elements depending of it.
	// The implementation is very naive, and could be improved for more performance
	// The UI uses a local coordinates system, to account for reshapes, and different window sizes
	// UI elements coordinates must be using those coordinates
	class GUI {
	private :
		std::vector<GUIElement> components;
		const Vector2f coordinatesSystem;
	
	public:
		GUI() = delete;
		GUI(float sizeX, float sizeY);

		// Transcribe a position from window coordinates to the local coordinate system of the GUI
		Vector2f translateCoordinates(const Vector2f& position);

		/*
		* Updates the state of the components of the window
		*/
		void update();

		// Adds an element to the interface
		void addElement(GUIElement& element);

	};
}
