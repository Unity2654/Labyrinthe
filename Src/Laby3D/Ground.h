#pragma once

#include "../GlOOPLib/Objects/Object3D.h"
#include "../GlOOPLib/Textures/Texture.h"

class Ground : public gloop::Object3D
{
private:
    float sizeX;
    float sizeZ;
    gloop::Texture texture;

public:
    /**
     * @brief Construct a new Ground object
     * @param sizeX The size of the ground on the X axis
     * @param sizeZ The size of the ground on the Z axis
     * The ground is centered on the origin, so it goes from -sizeX/2 to sizeX/2 on the X axis, and from -sizeZ/2 to sizeZ/2 on the Z axis
     */
    Ground(float sizeX, float sizeZ);

    /**
     * @brief Draws a cube, only the top face, with a texture, for the ground
     * @param facettesX The number of the facettes on the X axis
     * @param facettesZ The number of the facettes on the Z axis
     */
    void drawCube(int facettesX, int facettesZ);

    /**
     * @brief Renders the ground
     */
    void render() override;
};
