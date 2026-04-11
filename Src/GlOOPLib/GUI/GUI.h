#pragma once
#include <vector>
#include "GUIElement.h"

namespace gloop {

	/** A graphical user interface.
	*	Once updated, it checks the mouse position and state and updates the registered (enabled) GUI elements depending of it.
	*	The implementation is very naive, and could be improved for more performance
	*/
	class GUI {
	private :
		std::vector<GUIElement> components;
	
	public:
		GUI() = default;

		/*
		* Updates the state of thge components of the window
		*/
		void update();

		// Adds an element to the interface
		void addElement(GUIElement& element);

	};
}
