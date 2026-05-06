#pragma once

#include "../GlOOPLib/Objects/Object3D.h"
#include "../GlOOPLib/Textures/Texture.h"

class Sky : public gloop::Object3D {
private :
	float sizeX;
	float sizeZ;
	float sizeY;
	float positionY;

	gloop::Texture texture;

public :
	Sky(float sizeX, float sizeZ, float sizeY, float positionY);

	void drawSky(int facettesX, int facettesZ);

	void render() override;
};