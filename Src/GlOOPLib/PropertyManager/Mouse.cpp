#include "Mouse.h"
#include <stdlib.h>
#include <GL/glut.h>
#include "GlPropertyManager.h"

namespace gloop {

	Mouse::Mouse() : position(0.0,0.0), movementDelta(0.0,0.0), clickStartPosition(0.0,0.0){}

	void Mouse::moveTo(Vector2f newPosition){
		auto c = prop::getDisplay().getCenter();
		if (isWarpEnabled && ((newPosition.x != c.x) || (newPosition.y != c.y)) ) {
				movementDelta = movementDelta + (newPosition - position);
				glutWarpPointer(c.x, c.y);
        		position = c;
		}
		else{
			movementDelta = movementDelta + (newPosition - position);
			position = newPosition;
		}
	}


	void Mouse::update(){
		movementDelta = Vector2f(0.0f, 0.0f);
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

	const Vector2f& Mouse::getClickStartPosition() const{
		return clickStartPosition;
	}

	const Vector2f Mouse::getMovement() const{
		return movementDelta;
	}

	const MouseState& Mouse::getState() const{
		return buttonsState;
	}

}
