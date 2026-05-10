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
    const gloop::Material displayMaterial{ gloop::Color{1.0,1.0,1.0,1.0}, gloop::Color{1.0,1.0,1.0,1.0} };


public:
    /**
     *  @brief Construct a new End Door:: End Door object
     * @param posX The X position of the door
     * @param posZ The Z position of the door
     * @param height The height of the door
     * @param width The width of the door
     * @param rotation The rotation of the door, in degrees, around the Y axis
     * @param scene The scene in which the door is located, used to add the particles to it
     */
    EndDoor(float posX, float posZ, float height, float width, float rotation, gloop::Scene &scene);
    
    /**
     * @brief Destroy the End Door, disable the light
     */
    ~EndDoor();

    /**
     * @brief Renders the door, with a texture and a light
     */
    void render() override;

    /**
     * @brief Updates the door to check if the player enters it, and if so, switch to the end scene
    */
    void update() override;

    /**
     * @brief Draws a cube, for the surroundings of the door
    */
    void drawCube();

    gloop::CollisionBox getCollisionBox() const override;
};
