#pragma once

#include "GlOOPLib/Objects/Object3D.h"

class Wall : public gloop::Object3D
{
private:
    float posX;
    float posZ;
    float width;
    float thickness;
    float height;
    float rotation;

public:
    Wall(float posX, float posZ, float width, float thickness, float height, float rotation);

    void render() override;
};
