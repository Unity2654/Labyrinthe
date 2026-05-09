#pragma once

#include "../GlOOPLib/Scenes/Scenes.h"
#include "../Laby3D/Laby3D.h"
#include "Character.h"
#include "Sky.h"

// The scene the labyrinthe is displayed in
class LabyrintheScene: public gloop::Scene {
private:

	// Constants for the creation of the maze
	// Allows the use a default constructor for the scene

	static constexpr float Y_SIZE = 4.0f;         // size of the maze in y axis
	static constexpr float WALL_THICKNESS = 0.2f; // width of the walls
	static constexpr float PILLAR_WIDTH = 0.4f;   // width of the pillars*
	// Creation of the 2D tab
	static constexpr int WIDTH = 3;		      
	static constexpr int HEIGHT = 4;

	static constexpr float X_SIZE = 3*WIDTH;        // size of the maze in x axis
	static constexpr float Z_SIZE = 3*HEIGHT;        // size of the maze in z axis

	Laby3D laby;
	Character player;
	Sky skybox;

	gloop::DirectionalLight mapLight = gloop::DirectionalLight(GL_LIGHT1, {{ 0.3f, 0.3f, 0.3f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f, 1.0f}} ,{ 0.0f, -1.0f, 0.0f });

	void drawMinimap(gloop::Display& window);

public:

	LabyrintheScene();

	const std::vector<gloop::CollisionBox> getNearbyHitboxes(const gloop::Vector3f& position) const;

	Character& getPlayer();

	virtual void onLoad() override;
	virtual void onDeLoad() override;

	virtual void display() override;

	virtual void update() override;

};