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
	EndScene();

	virtual void update() override;
	virtual void display() override;
	virtual void onLoad() override;
};