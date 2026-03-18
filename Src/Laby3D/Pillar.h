#pragma once

#include "GlOOPLib/Objects/Object3D.h"

class Pillar : public gloop::Object3D
{
private:
    float posX;
    float posZ;
    float thickness;
    float height;

public:
    Pillar(float posX, float posZ, float thickness, float height);

    void render() override;
};
