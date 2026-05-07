#pragma once

#include "../GlOOPLib/Objects/Entity3D.h"
#include "../GlOOPLib/Physics/Collidable.h"
#include "../GlOOPLib/Lights/Materials.h"
#include "../GlOOPLib/Textures/Texture.h"
#include "../GlOOPLib/Scenes/Scenes.h"


class EndDoor : public gloop::Entity3D, public gloop::Collidable
{
protected:
    float posX;
    float posZ;
    float height;
    float width;
    float rotation;
    //const gloop::Material displayMaterial{ gloop::Color{1.0,0.0,0.0,1.0}, gloop::Color{1.0,0.0,0.0,1.0} };
    // const gloop::Material displayMaterial{ gloop::Color{1.0,1.0,1.0,1.0}, gloop::Color{1.0,1.0,1.0,1.0} };
    const gloop::CollisionBox hitbox;
    const gloop::Texture texture;
    gloop::Scene &scene;
    int alpha = 0;


public:
    EndDoor(float posX, float posZ, float height, float width, float rotation, gloop::Scene &scene);
    
    ~EndDoor();

    void render() override;

    void update() override;

    void drawCube();

    gloop::CollisionBox getCollisionBox() const override;
};
