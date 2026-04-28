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
    Ground(float sizeX, float sizeZ);

    void drawCube(int facettesX, int facettesZ);

    void render() override;
};
