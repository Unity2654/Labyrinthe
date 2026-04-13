#include "MenuElements.h"
#include "../GlOOPLib/PropertyManager/GlPropertyManager.h"
#include "../GlOOPLib/GUI/Text.h"

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

MovingPillar::MovingPillar(gloop::Vector2f basePosition, gloop::Vector2f minPosition, gloop::Vector2f maxPosition, float time, float thickness, float height):
	Pillar(basePosition.x, basePosition.y, thickness, height),
	minPosition(minPosition),
	maxPosition(maxPosition),
	speed((minPosition - maxPosition) / time / prop::FPS),
	distance((minPosition - maxPosition).norm()) {}

void MovingPillar::update(){
	posX = posX + speed.x;
	posZ = posZ + speed.y;

	if (gloop::Vector2f(posX - maxPosition.x, posZ - maxPosition.y).norm() >= distance) {
		posX = maxPosition.x;
		posZ = maxPosition.y;
	}
}

void MovingPillar::render(){
	Pillar::render();
}

MenuButton::MenuButton(gloop::Vector3f position, float width, float height, std::shared_ptr<gloop::GUIElement> interface) :
	position(position),
	interface(interface),
	width(width),
	height(height)
{}

void MenuButton::render(){
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glScalef(width, height, 0.0);

	if (interface->isClicked())
		click.apply(GL_FRONT);
	else if (interface->isHovered())
		hover.apply(GL_FRONT);
	else
		default.apply(GL_FRONT);
	
	gloop::glyphs::E();

	glPopMatrix();
}

TitleText::TitleText(gloop::Vector3f position) : position{position.x, position.y, position.z}{}

void TitleText::render()
{
}

