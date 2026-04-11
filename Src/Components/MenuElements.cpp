#include "MenuElements.h"
#include "../GlOOPLib/PropertyManager/GlPropertyManager.h"

MovingWall::MovingWall(gloop::Vector2f basePosition, gloop::Vector2f minPosition, gloop::Vector2f maxPosition, float time, float width, float thickness, float height, float rotation):
	Wall(basePosition.x, basePosition.y, width, thickness, height, rotation),
	minPosition(minPosition),
	maxPosition(maxPosition),
	speed((minPosition - maxPosition) / time / prop::FPS),
	distance((minPosition - maxPosition).norm()){}

void MovingWall::update(){
	posX = posX + speed.x;
	posZ = posZ + speed.y;

	if (gloop::Vector2f(posX - maxPosition.x, posZ - maxPosition.y).norm() >= distance) {
		posX = maxPosition.x;
		posZ = maxPosition.y;
	}
}

void MovingWall::render(){
	Wall::render();
}