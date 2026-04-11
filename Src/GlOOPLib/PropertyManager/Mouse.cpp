#include "Mouse.h"

namespace gloop {

	Mouse::Mouse() : position(0.0,0.0), previousPosition(0.0,0.0), clickStartPosition(0.0,0.0){}

	void Mouse::update(Vector2f newPosition){
		previousPosition = position;
		position = newPosition;
		if (buttonsState.leftButton == RELEASE)
			buttonsState.leftButton = NONE;
		if (buttonsState.rightButton == RELEASE)
			buttonsState.rightButton = NONE;
	}

	void Mouse::click(){
		buttonsState.leftButton = DOWN;
		clickStartPosition = position;
	}

	void Mouse::rightClick(){
		buttonsState.rightButton = DOWN;
	}

	void Mouse::releaseClick(){
		buttonsState.leftButton = RELEASE;
	}

	void Mouse::releaseRightClick(){
		buttonsState.rightButton = RELEASE;
	}

	const Vector2f& Mouse::getPosition() const{
		return position;
	}

	const Vector2f& Mouse::getPreviousPosition() const{
		return previousPosition;
	}

	const Vector2f& Mouse::getClickStartPosition() const{
		return clickStartPosition;
	}

	const Vector2f& Mouse::getMovement() const{
		return position - previousPosition;
	}

	const MouseState& Mouse::getState() const{
		return buttonsState;
	}

}
