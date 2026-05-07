#include "MenuElements.h"
#include "../GlOOPLib/PropertyManager/GlPropertyManager.h"
#include "../GlOOPLib/GUI/Text.h"
#include <GL/glut.h>
#include "LabyrintheScene.h"

MovingWall::MovingWall(gloop::Vector2f basePosition, gloop::Vector2f minPosition, gloop::Vector2f maxPosition, float time, float width, float thickness, float height, float rotation):
	Wall(basePosition.x, basePosition.y, width, thickness, height, rotation),
	minPosition(minPosition),
	maxPosition(maxPosition),
	speed((minPosition - maxPosition) / time / prop::FPS),
	distance((minPosition - maxPosition).norm()){
}

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
		defaultMaterial.apply(GL_FRONT);
	
	gloop::glyphs::S();

	glPopMatrix();
}

TitleText::TitleText(gloop::Vector3f position) : position{position.x, position.y, position.z}{}

void TitleText::render(){
	gloop::Vector3f pos = position;
	TextMaterial.renderWithMaterial(GL_FRONT, [pos]() {
		float letterSpace = 1.0f;
		glPushMatrix();

		glTranslatef(pos.x, pos.y, pos.z);
		glScalef(0.2, 0.2, 0.0);
		glTranslatef((4.5*letterSpace), 0.0, 0.0);
		// L
		gloop::glyphs::L();
		// A
		glTranslatef(-letterSpace, 0.0, 0.0);
		gloop::glyphs::A();
		// B
		glTranslatef(-letterSpace, 0.0, 0.0);
		gloop::glyphs::B();
		// Y
		glTranslatef(-letterSpace, 0.0, 0.0);
		gloop::glyphs::Y();
		// R
		glTranslatef(-letterSpace, 0.0, 0.0);
		gloop::glyphs::R();
		// I
		glTranslatef(-letterSpace, 0.0, 0.0);
		gloop::glyphs::I();
		// N
		glTranslatef(-letterSpace, 0.0, 0.0);
		gloop::glyphs::N();
		// T
		glTranslatef(-letterSpace, 0.0, 0.0);
		gloop::glyphs::T();
		// H
		glTranslatef(-letterSpace, 0.0, 0.0);
		gloop::glyphs::H();
		// E
		glTranslatef(-letterSpace, 0.0, 0.0);
		gloop::glyphs::E();

		glPopMatrix();
	});
}

StartButton::StartButton(gloop::Vector3f position, float width, float height, std::shared_ptr<gloop::GUIElement> interface) :
	position(position),
	interface(interface),
	width(width),
	height(height){}

void StartButton::render(){
	gloop::Material old = gloop::Material::getCurrentMaterial(GL_FRONT);

	// Text
	gloop::Vector3f pos = position;
	auto w = width/6;
	defaultMaterial.apply(GL_FRONT);
	float letterSpace = 1.0f;
	glPushMatrix();

	glTranslatef(pos.x, pos.y, pos.z);
	glScalef(w, w, 0.0);
	glTranslatef((2 * letterSpace), 0.0, 0.0);
	// S
	gloop::glyphs::S();
	// T
	glTranslatef(-letterSpace, 0.0, 0.0);
	gloop::glyphs::T();
	// A
	glTranslatef(-letterSpace, 0.0, 0.0);
	gloop::glyphs::A();
	// R
	glTranslatef(-letterSpace, 0.0, 0.0);
	gloop::glyphs::R();
	// T
	glTranslatef(-letterSpace, 0.0, 0.0);
	gloop::glyphs::T();

	glPopMatrix();

	// Rectangle
	glPushMatrix();

	glTranslatef(pos.x, pos.y, pos.z);
	glRotatef(rotation, 1.0, 0.0, 0.0);
	glScalef(width, height, height);

	if (interface->isHovered())
		hover.apply(GL_FRONT);

	glutWireCube(1.0);

	glPopMatrix();

	old.apply(GL_FRONT);

}

void StartButton::update(){
	if (interface->isClicked()){
		LabyrintheScene lb;
		prop::getSceneManager().pushScene(lb);
	}
	else if (interface->isHovered())
		rotationspeed = HOVER_ROTATION_SPEED;
	else
		rotationspeed = DEFAULT_ROTATION_SPEED;
	rotation += rotationspeed;
}

MovingGround::MovingGround(gloop::Vector2f basePosition, gloop::Vector2f minPosition, gloop::Vector2f maxPosition, float time, float width) :
	Ground(width, width),
	position(basePosition),
	minPosition(minPosition),
	maxPosition(maxPosition),
	speed((minPosition - maxPosition) / time / prop::FPS),
	distance((minPosition - maxPosition).norm())
{}

void MovingGround::render() {
	glPushMatrix();
	glTranslatef(position.x, 0.0f, position.y);
	Ground::render();
	glPopMatrix();
}

void MovingGround::update() {
	position = position + speed;

	if ((position - maxPosition).norm() >= distance) {
		position = maxPosition;
	}
}