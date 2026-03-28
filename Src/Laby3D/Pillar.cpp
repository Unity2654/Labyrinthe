#include "Pillar.h"

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

Pillar::Pillar(float posX, float posZ, float thickness, float height) : posX(posX), posZ(posZ), thickness(thickness), height(height)
{
}

void Pillar::render()
{
    glPushMatrix();
    glTranslatef(posX, height / 2, posZ);
    glScalef(thickness, height, thickness);
    float blue[] = {0.0, 0.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blue);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(posX, height / 20, posZ);
    glScalef(thickness * 1.2, height / 10, thickness * 1.5);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(posX, height - height / 20, posZ);
    glScalef(thickness * 1.2, height / 10, thickness * 1.5);
    glutSolidCube(1.0);
    glPopMatrix();
}