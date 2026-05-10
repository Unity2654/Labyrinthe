#pragma once

#include "../GlOOPLib/Objects/Object3D.h"
#include "../GlOOPLib/Physics/Collidable.h"
#include "../GlOOPLib/Lights/Materials.h"
#include "../GlOOPLib/Textures/Texture.h"

class Wall : public gloop::Object3D, public gloop::Collidable
{
protected:
    float posX;
    float posZ;
    float width;
    float thickness;
    float height;
    float rotation;
    //const gloop::Material displayMaterial{ gloop::Color{1.0,0.0,0.0,1.0}, gloop::Color{1.0,0.0,0.0,1.0} };
    const gloop::Material displayMaterial{ gloop::Color{1.0,1.0,1.0,1.0}, gloop::Color{1.0,1.0,1.0,1.0} };
    const gloop::CollisionBox hitbox;
    const gloop::Texture texture;

    void drawCube(int facettesX, int facettesY) const;

public:
    /**
     * @brief Construct a new Wall object
     * @param posX The X position of the wall
     * @param posZ The Z position of the wall
     * @param width The width of the wall
     * @param thickness The thickness of the wall
     * @param height The height of the wall
     * @param rotation The rotation of the wall, in degrees, around the Y axis
     */
    Wall(float posX, float posZ, float width, float thickness, float height, float rotation);

    /**
     * @brief Renders the wall, with a texture
     */
    void render() override;

    /**
     * @brief Get the collision box of the wall
     * @return The collision box of the wall
     */
    gloop::CollisionBox getCollisionBox() const override;
};
