#include "Ground.h"

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

Ground::Ground(float sizeX, float sizeZ) : sizeX(sizeX), sizeZ(sizeZ)
{
}

void Ground::drawCube(int facettesX, int facettesZ)
{
    float white[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);

    glNormal3f(0.0, 1.0, 0.0);

    float sizeFacettesX = 1.0 / facettesX;
    float sizeFacettesZ = 1.0 / facettesZ;
    for (int i = 0; i <= facettesZ; i++)
    {
        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= facettesX; j++)
        {
            glVertex3f(-0.5 + j * sizeFacettesX, 0.5, -0.5 + i * sizeFacettesZ);
            glVertex3f(-0.5 + j * sizeFacettesX, 0.5, -0.5 + (i + 1) * sizeFacettesZ);
        }
        glEnd();
    }
}

void Ground::render()
{
    glPushMatrix();
    glTranslatef(0, -0.1, 0);
    glScalef(sizeX, 0.2, sizeZ);

    drawCube(50, 50);
    glPopMatrix();
}