#pragma once

#include "Laby3D/Wall.h"
#include "GL/glut.h"
#include "GL/gl.h"
#include "GL/glu.h"

Wall::Wall(float posX, float posZ, float width, float thickness, float height, float rotation) : posX(posX), posZ(posZ), width(width), thickness(thickness), height(height), rotation(rotation)
{
}

void Wall::render()
{
    glPushMatrix();
    glTranslatef(posX, height / 2, posZ);
    glRotatef(rotation, 0, 1, 0);

    glScalef(width, height, thickness);
    float red[] = {1.0, 0.0, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
    glutSolidCube(1.0);
    glPopMatrix();
}