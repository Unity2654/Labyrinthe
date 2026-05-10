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
    gloop::Material displayMaterial{ gloop::Color{0.7f, 0.7f, 0.7f, 1.0f }, gloop::Color{0.7f, 0.7f, 0.7f, 1.0f} };
    gloop::Texture texture;

    void drawCube(int facettesX, int facettesY, float height) const;

public:
    /**
     * @brief Construct a new Pillar object
     * @param posX The X position of the pillar
     * @param posZ The Z position of the pillar
     * @param thickness The thickness of the pillar
     * @param height The height of the pillar
     */
    Pillar(float posX, float posZ, float thickness, float height);

    /**
     * @brief Renders the pillar, with a texture
     */
    void render() override;

    /**
    * @brief Get the collision box of the pillar
    * @return The collision box of the pillar
    */
    gloop::CollisionBox getCollisionBox() const override;
};
