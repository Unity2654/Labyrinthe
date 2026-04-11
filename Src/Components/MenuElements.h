#pragma once
#include "../Laby3D/Wall.h"
#include "../GlOOPLib/Objects/Entity3D.h"


// A wall that moves
// The wall moves from minPosition to maxPosition in a given time in seconds
// min and max positions must not overlap
class MovingWall : public Wall, public gloop::Entity3D {
private :
	gloop::Vector2f minPosition;
	gloop::Vector2f maxPosition;
	gloop::Vector2f speed;
	const float distance;

public :

	MovingWall(gloop::Vector2f basePosition, gloop::Vector2f minPosition, gloop::Vector2f maxPosition, float time, float width, float thickness, float height, float rotation);

	void update() override;
	void render() override;
};