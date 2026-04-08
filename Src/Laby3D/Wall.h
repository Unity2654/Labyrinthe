#pragma once

#include "../GlOOPLib/Objects/Object3D.h"
#include "../GlOOPLib/Physics/Collidable.h"
#include "../GlOOPLib/Lights/Materials.h"

class Wall : public gloop::Object3D, public gloop::Collidable
{
private:
    float posX;
    float posZ;
    float width;
    float thickness;
    float height;
    float rotation;
    const gloop::Material displayMaterial{ gloop::Color{1.0,0.0,0.0,1.0}, gloop::Color{1.0,0.0,0.0,1.0} };
    const gloop::CollisionBox hitbox;

    void drawCube(int facettesX, int facettesY) const;

public:
    Wall(float posX, float posZ, float width, float thickness, float height, float rotation);

    void render() override;

    gloop::CollisionBox getCollisionBox() const override;
};
