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

		MouseState buttonsState;

	public :
		Mouse();

		// Update state
		void update(Vector2f& newPosition);

		void click();
		void rightClick();
		void releaseClick();
		void releaseRightClick();

		// Getters
		const Vector2f& getPosition() const;

		const Vector2f& getPreviousPosition() const;

		const Vector2f& getMovement() const;

		const MouseState& getState() const;
	};
}