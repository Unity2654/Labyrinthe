#pragma once
#include "../GlOOPLib/Scenes/Scenes.h"
#include "../GlOOPLib/GUI/GUI.h"

class MenuScene : public gloop::Scene {
private :
	static constexpr float X_SIZE = 30.0f;
	static constexpr float Z_SIZE = 5.0f;        // size of the maze in z axis
	static constexpr float Y_SIZE = 4.0f;         // size of the maze in y axis
	static constexpr float WALL_THICKNESS = 0.2f; // width of the walls
	static constexpr float PILLAR_WIDTH = 0.4f;   // width of the pillars

	const gloop::Vector2f initialPosition = { 1.5, -2.5 };
	const gloop::Vector2f finalPosition = { 1.5,20.0 };
	const gloop::Vector2f symmetryFactor = { -1.0,1.0 };

	const gloop::Vector3f POS = gloop::Vector3f(0, 1.75, 0);

	gloop::PonctualLight light1 = gloop::PonctualLight(
        GL_LIGHT0, { {0.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 0.77f, 0.09f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f} }, 
        POS, 
        { 0.0f, 0.3f, 0.1f }
    );
    // Lumiere rouge moins intense
    gloop::PonctualLight light2 = gloop::PonctualLight(
        GL_LIGHT1, { {0.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 0.1f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f} }, 
        POS, 
        { 0.0f, 0.5f, 0.2f }
    );
    // Lumiere jaune encore moins intense mais plus large
    gloop::PonctualLight light3 = gloop::PonctualLight(
        GL_LIGHT2, { {0.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f} }, 
        POS, 
        { 0.0f, 0.5f, 0.0f }
    );

	gloop::GUI UI;

public :
	MenuScene();

	virtual void update() override;
	virtual void display() override;
	virtual void onLoad() override;
};