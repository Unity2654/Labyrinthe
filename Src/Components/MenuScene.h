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
    /**
     * @brief Construct a new Menu Scene object, with the moving pillars, the title of the game and the button to start the game
     */
	MenuScene();

    /**
     * @brief Updates the scene, check if the button is clicked and update the position of the pillars and walls
     */
	virtual void update() override;
    /**
     * @brief Displays the scene
     */
	virtual void display() override;
    /**
     * @brief Called when the scene is loaded, used to initialize the scene
     */
	virtual void onLoad() override;
};