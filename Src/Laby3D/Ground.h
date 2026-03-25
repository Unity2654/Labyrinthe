#pragma once

#include "GlOOPLib/Objects/Object3D.h"

class Ground : public gloop::Object3D
{
private:
    float sizeX;
    float sizeZ;

public:
    Ground(float sizeX, float sizeZ);

    void drawCube(int facettesX, int facettesZ);

    void render() override;
};
