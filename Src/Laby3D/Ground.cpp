#include "Laby3D/Ground.h"

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

Ground::Ground(float sizeX, float sizeZ) : sizeX(sizeX), sizeZ(sizeZ)
{
}

void Ground::render()
{
    glPushMatrix();
    glTranslatef(0, -0.1, 0);
    glScalef(sizeX, 0.2, sizeZ);
    float white[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
    glutSolidCube(1.0);
    glPopMatrix();
}