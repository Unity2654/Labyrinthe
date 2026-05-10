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
    Character(gloop::Vector3f pos);
    ~Character();

    void updateMovement();
    void updateLight();

    void update() override;
    void render() override;
    void renderOnMap(float scale);

    void setLookingAt(const gloop::Vector3f& dir);

    void Jump();

    void switchCamera();
    bool isFirstPerson() const;

    gloop::Vector3f getPosition() const;

    void updateMouse();

    gloop::CollisionBox getCollisionBox() const override;
};