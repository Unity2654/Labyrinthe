#pragma once
#include "../Maths/Vector.h"

namespace gloop {
	
	enum MouseButtonState{
		NONE,
		DOWN,
		RELEASE,
	};

	struct MouseState {
		MouseButtonState leftButton;
		MouseButtonState rightButton;

		MouseState() : leftButton(NONE), rightButton(NONE){}
	};

	class Mouse {
	private :
		Vector2f position;
		Vector2f previousPosition;

		// Position of the mouse when the user starts clicking
		// Can be important for when the user : starts clicking on a box -> drags its mouse outside of the box -> stops clicking
		// Relevant only if the state of a button is "Released"
		Vector2f clickStartPosition;

		MouseState buttonsState;

	public :
		Mouse();

		// Warp
		bool isWarpEnabled = false;

		// Update state
		void moveTo(Vector2f newPosition);

		void update();

		void click();
		void rightClick();
		void releaseClick();
		void releaseRightClick();

		// Getters
		const Vector2f& getPosition() const;

		const Vector2f& getPreviousPosition() const;

		const Vector2f& getClickStartPosition() const;

		const Vector2f& getMovement() const;

		const MouseState& getState() const;
	};
}