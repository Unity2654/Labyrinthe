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

    // Lumiere orange
    gloop::PonctualLight light1 = gloop::PonctualLight(
        GL_LIGHT0, { {0.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 0.77f, 0.09f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f} }, 
        pos, 
        { 0.0f, 0.3f, 0.1f }
    );
    // Lumiere rouge moins intense
    gloop::PonctualLight light2 = gloop::PonctualLight(
        GL_LIGHT1, { {0.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 0.1f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f} }, 
        pos, 
        { 0.0f, 0.5f, 0.2f }
    );
    // Lumiere jaune encore moins intense mais plus large
    gloop::PonctualLight light3 = gloop::PonctualLight(
        GL_LIGHT2, { {0.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f} }, 
        pos, 
        { 0.0f, 0.5f, 0.0f }
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