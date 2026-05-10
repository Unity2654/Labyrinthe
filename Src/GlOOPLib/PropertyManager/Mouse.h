#pragma once
#include "../Maths/Vector.h"

namespace gloop {
	
	// Stores the state of a button of the mouse
	enum MouseButtonState{
		// No button is pressed
		NONE,
		// The button is currently being pressed
		DOWN,
		// The button was released in the current frame
		RELEASE,
	};

	// Data structure storing the state of both of the buttons of the mouse
	struct MouseState {
		MouseButtonState leftButton;
		MouseButtonState rightButton;

		MouseState() : leftButton(NONE), rightButton(NONE){}
	};

	// Class storing the main properties of the user's mouse, if it is within the window
	class Mouse {
	private :
		// Position of the mouse
		Vector2f position;
		Vector2f movementDelta;

		// Position of the mouse when the user starts clicking
		// Can be important for when the user : starts clicking on a box -> drags its mouse outside of the box -> stops clicking
		// Relevant only if the state of a button is "Released"
		Vector2f clickStartPosition;

		// State of the buttons of the mouse
		MouseState buttonsState;

	public :
		Mouse();

		// Warp
		bool isWarpEnabled = false;

		// Update state
		void moveTo(Vector2f newPosition);
		
		// Updates the state of the mouse for the current frame
		void update();

		// Indicates the user left clicked with the mouse
		void click();
		// Indicates the user right clicked with the mouse
		void rightClick();
		// Indicates the user released its left click with the mouse
		void releaseClick();
		// Indicates the user released its right click with the mouse
		void releaseRightClick();

		// Returs the current position of the mouse
		const Vector2f& getPosition() const;
		// Returns the position where the user started to click
		const Vector2f& getClickStartPosition() const;
		// Return the movement made by the mouse of the user between the last frame and the current one
		const Vector2f getMovement() const;
		// Returns the state of the buttons of the mouse
		const MouseState& getState() const;
	};
}