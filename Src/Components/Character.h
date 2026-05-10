#pragma once

#include "../GlOOPLib/Maths/Vector.h"
#include "../GlOOPLib/Objects/Entity3D.h"
#include "../GlOOPLib/Camera/Camera.h"
#include "../GlOOPLib/PropertyManager/GlPropertyManager.h"
#include "../GlOOPLib/Physics/Collidable.h"
#include "../GlOOPLib/Lights/Lights.h"
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

class Character : public gloop::Entity3D, public gloop::Collidable
{
private:
    gloop::Vector3f pos;
    gloop::Vector2f speed;
    float jump;
    int moving[4];
    bool isSprinting;
    float rotate_x;
    float rotate_y;

    gloop::Vector3f looking_at;

    gloop::CameraPerspective camFP;
    gloop::CameraOrtho camMap;

    gloop::PonctualLight lightWhite = gloop::PonctualLight(
        GL_LIGHT0,
        {
            {0.0f, 0.0f, 0.0f, 1.0f},
            {1.0f, 0.95f, 0.85f, 1.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        },
        pos,
        {1.0f, 0.4f, 0.2f}
    );

    gloop::PonctualLight lightYellow = gloop::PonctualLight(
        GL_LIGHT1,
        {
            {0.0f, 0.0f, 0.0f, 1.0f},
            {1.0f, 0.80f, 0.25f, 1.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        },
        pos,
        {1.0f, 0.3f, 0.18f}
    );

    gloop::PonctualLight lightOrange = gloop::PonctualLight(
        GL_LIGHT2,
        {
            {0.0f, 0.0f, 0.0f, 1.0f},
            {1.0f, 0.45f, 0.08f, 1.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        },
        pos,
        {1.0f, 0.22f, 0.07f}
    );

    gloop::PonctualLight lightRed = gloop::PonctualLight(
        GL_LIGHT3,
        {
            {0.0f, 0.0f, 0.0f, 1.0f},
            {0.35f, 0.03f, 0.0f, 1.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        },
        pos,
        {1.0f, 0.12f, 0.05f}
    );


    bool fp; // true = 1st person, false = map

public:
    /**
     * @brief Construct a new Character object
     * @param pos The initial position of the character
     */
    Character(gloop::Vector3f pos);
    /**
     * @brief Destroy the Character object, disable the lights
     */
    ~Character();

    /**
     * @brief Checks the input and updates the character's position
     */
    void updateMovement();
    /**
     * @brief Updates the position of the lights to follow the character, and render them
     */
    void updateLight();
    /**
     * @brief Updates the direction of the camera according to the mouse movement
     */
    void updateMouse();

    /**
     *  @brief run the updates
     */
    void update() override;
    /**
     * @brief Renders the character if it's not in first person and updates the camera
     */
    void render() override;
    /**
     * @brief Renders the character on the map, with a given scale (the size of the character on the map)
     * @param scale The size of the character on the map
     */
    void renderOnMap(float scale);

    /**
     * @brief Set the looking at direction of the character, used to update the camera direction
     * @param dir The new looking at direction of the character
     */
    void setLookingAt(const gloop::Vector3f& dir);

    /**
     * @brief Makes the character jump
     */
    void Jump();

    /**
     * @brief Switches the camera mode between first person and map
     */
    void switchCamera();
    /**
     * @brief Checks if the character is in first person mode
     * @return true if the character is in first person mode, false otherwise
     */
    bool isFirstPerson() const;

    /**
     * @brief Get the position of the character
     * @return The position of the character
     */
    gloop::Vector3f getPosition() const;

    /**
     * @brief Get the collision box of the character, used for collision detection
     * @return The collision box of the character
     */
    gloop::CollisionBox getCollisionBox() const override;
};