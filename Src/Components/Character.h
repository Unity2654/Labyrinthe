#pragma once

#include "../GlOOPLib/Maths/Vector.h"
#include "../GlOOPLib/Objects/Entity3D.h"
#include "../GlOOPLib/Camera/Camera.h"
#include "../GlOOPLib/PropertyManager/GlPropertyManager.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

class Character : public gloop::Entity3D
{
private:
    gloop::Vector3f pos;
    float jump;
    int moving[4];
    bool isSprinting;
    float rotate_x;
    float rotate_y;

    gloop::Vector3f looking_at;

    gloop::CameraPerspective camFP;
    gloop::CameraOrtho camMap;
    bool fp; // true = 1st person, false = map

public:
    Character(gloop::Vector3f pos);


    void updateMovement();


    void update() override;
    void render() override;

    void setLookingAt(const gloop::Vector3f& dir);

    void Jump();

    void switchCamera(); 

    gloop::Vector3f getPosition() const;

    void updateMouse();
};