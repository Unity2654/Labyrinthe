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
	/**
	 * @brief Construct a new Sky object
	 * @param sizeX The size of the sky in the X axis
	 * @param sizeZ The size of the sky in the Z axis
	 * @param sizeY The size of the sky in the Y axis
	 * @param positionY The position of the sky in the Y axis
	 */
	Sky(float sizeX, float sizeZ, float sizeY, float positionY);

	/**
	 * @brief Draws the sky
	 */
	void drawSky(int facettesX, int facettesZ);

	/**
	 * @brief Renders the sky
	 */
	void render() override;
};