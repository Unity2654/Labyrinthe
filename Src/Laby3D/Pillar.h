#pragma once

#include "../GlOOPLib/Objects/Object3D.h"
#include "../GlOOPLib/Lights/Materials.h"

class Pillar : public gloop::Object3D
{
private:
    float posX;
    float posZ;
    float thickness;
    float height;
    gloop::Material displayMaterial{};


public:
    Pillar(float posX, float posZ, float thickness, float height);

    void render() override;
};
