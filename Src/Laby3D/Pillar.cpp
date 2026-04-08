#include "Pillar.h"

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

//#define SHOW_HITBOX

Pillar::Pillar(float posX, float posZ, float thickness, float height) : posX(posX), posZ(posZ), thickness(thickness), height(height)
{
}

void Pillar::render()
{
    displayMaterial.apply(GL_FRONT_AND_BACK);
#ifdef SHOW_HITBOX // Show hitbox for debug purposes
    Collidable::drawHitbox(height);
#else
    glPushMatrix();
    glTranslatef(posX, height / 2, posZ);
    glScalef(thickness, height, thickness);
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
#endif
}

gloop::CollisionBox Pillar::getCollisionBox() const{
    return { gloop::Rectangle::fromCenter({ posX, posZ }, thickness, thickness) };
}
