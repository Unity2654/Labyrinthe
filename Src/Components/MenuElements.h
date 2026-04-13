#pragma once
#include "../Laby3D/Wall.h"
#include "../GlOOPLib/Objects/Entity3D.h"
#include "../Laby3D/Pillar.h"
#include "../GlOOPLib/GUI/GUIElement.h"
#include "../GlOOPLib/GUI/GUI.h"
#include <memory>


// A wall that moves
// The wall moves from maxPosition to minPosition in a given time in seconds
// min and max positions must not overlap, and the time must be a positive integer
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

// A Pillar that moves 
// The pillar moves from maxPosition to minPosition in a given time in seconds
// min and max positions must not overlap, and the time must be a positive integer
class MovingPillar : public Pillar, public gloop::Entity3D {
private:
	gloop::Vector2f minPosition;
	gloop::Vector2f maxPosition;
	gloop::Vector2f speed;
	const float distance;

public:

	// Pillar(float posX, float posZ, float thickness, float height);

	MovingPillar(gloop::Vector2f basePosition, gloop::Vector2f minPosition, gloop::Vector2f maxPosition, float time, float thickness, float height);

	void update() override;
	void render() override;
};

class MenuButton : public gloop::Object3D {
private :
	std::shared_ptr<gloop::GUIElement> interface;
	gloop::Vector3f position;
	float width;
	float height;

	gloop::Material default{{0.5, 0.5, 0.5, 1.0}, { 0.5,0.5,0.5,1.0 }};
	gloop::Material hover{{0.0, 0.0, 1.0, 1.0}, { 0.0,0.0,1.0,1.0 }};
	gloop::Material click{{1.0, 0.0, 0.0, 1.0}, { 1.0,0.0,0.0,1.0 }};


public :
	MenuButton(gloop::Vector3f position, float width, float height, std::shared_ptr<gloop::GUIElement> interface);

	void render() override;
};

class TitleText : public gloop::Object3D {
private :
	gloop::Vector3f position;
	gloop::Material TextMaterial{ {0.0, 0.0, 0.0, 1.0}, { 0.0,0.0,0.0,1.0 }, { 0.0,0.0,0.0,1.0 }, { 1.0,1.0,1.0,1.0 } };

public :
	TitleText(gloop::Vector3f position);

	void render() override;
};