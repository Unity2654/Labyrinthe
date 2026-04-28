#pragma once

#include "../GlOOPLib/Objects/Object3D.h"
#include "../GlOOPLib/Lights/Materials.h"
#include "../GlOOPLib/Physics/Collidable.h"
#include "../GlOOPLib/Textures/Texture.h"

class Pillar : public gloop::Object3D, public gloop::Collidable
{
protected:
    float posX;
    float posZ;
    float thickness;
    float height;
    gloop::Material displayMaterial{ gloop::Color{0.0, 0.0, 1.0, 1.0 }, gloop::Color{0.0, 0.0, 1.0, 1.0} };
    gloop::Texture texture;

    void drawCube(int facettesX, int facettesY, float height) const;

public:
    Pillar(float posX, float posZ, float thickness, float height);

    void render() override;

    gloop::CollisionBox getCollisionBox() const override;
};
