#pragma once
#include "../GlOOPLib/Scenes/Scenes.h"

class MenuScene : public gloop::Scene {
private :
	static constexpr float X_SIZE = 30.0f;
	static constexpr float Z_SIZE = 5.0f;        // size of the maze in z axis
	static constexpr float Y_SIZE = 4.0f;         // size of the maze in y axis
	static constexpr float WALL_THICKNESS = 0.2f; // width of the walls
	static constexpr float PILLAR_WIDTH = 0.4f;   // width of the pillars

	const gloop::Vector3f POS = gloop::Vector3f(0, 1.75, 0);

public :
	MenuScene();

	virtual void display() override;
};