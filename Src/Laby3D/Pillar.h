#pragma once

#include "../GlOOPLib/Objects/Object3D.h"
#include "../GlOOPLib/Lights/Materials.h"
#include "../GlOOPLib/Physics/Collidable.h"

class Pillar : public gloop::Object3D, public gloop::Collidable
{
protected:
    float posX;
    float posZ;
    float thickness;
    float height;
    gloop::Material displayMaterial{ gloop::Color{0.0, 0.0, 1.0, 1.0 }, gloop::Color{0.0, 0.0, 1.0, 1.0} };


public:
    Pillar(float posX, float posZ, float thickness, float height);

    void render() override;

    gloop::CollisionBox getCollisionBox() const override;
};
