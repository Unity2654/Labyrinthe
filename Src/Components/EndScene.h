#pragma once

#include "../GlOOPLib/Scenes/Scenes.h"
#include "../GlOOPLib/GUI/GUI.h"


class EndScene : public gloop::Scene {
private :
	const gloop::Vector3f POS = gloop::Vector3f(0, 1.75, 0);

	const gloop::PonctualLight light = gloop::PonctualLight(
		GL_LIGHT0,
		gloop::LightData{ {0.0f,0.0f,0.0f,1.0f}, {0.7f,0.7f,0.7f,1.0f} },
		{ 0.0f,0.0f,0.0f });

	gloop::GUI UI;

public :
	/**
	 * @brief Construct a new End Scene object, with the end door and the button to go back to the menu
	 */
	EndScene();

	/**
	 * @brief Updates the scene, check if the button is clicked
	 */
	virtual void update() override;
	/**
	 * @brief Displays the scene, with the end door and the button to go back to the menu
	 */
	virtual void display() override;
	/**
	 * @brief Called when the scene is loaded, used to initialize the scene
	 */
	virtual void onLoad() override;
};