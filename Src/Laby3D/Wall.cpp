#include "Laby3D/Wall.h"
#include "GL/glut.h"
#include "GL/gl.h"
#include "GL/glu.h"
#include <stdlib.h>

Wall::Wall(float posX, float posZ, float width, float thickness, float height, float rotation) : posX(posX), posZ(posZ), width(width), thickness(thickness), height(height), rotation(rotation)
{
}

void Wall::drawCube(int facettesX, int facettesY)
{
    float red[] = {1.0, 0.0, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
    glPushMatrix();

    for (int i = 0; i < facettesX; i++)
    {
        glBegin(GL_QUADS);
        glNormal3f(0.0, 1.0, 0.0);
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(0.5, 0.5, -0.5);
        glVertex3f(-0.5, 0.5, -0.5);
        glVertex3f(-0.5, 0.5, 0.5);
        glEnd();

        for (int j = 0; j < facettesY; j++)
        {
            glBegin(GL_QUADS);
            glNormal3f(0.0, 0.0, 1.0);
            glVertex3f(-0.5 + i * (1.0 / facettesX), -0.5 + j * (1.0 / facettesY), 0.5);
            glVertex3f(-0.5 + i * (1.0 / facettesX), -0.5 + (j + 1) * (1.0 / facettesY), 0.5);
            glVertex3f(-0.5 + (i + 1) * (1.0 / facettesX), -0.5 + (j + 1) * (1.0 / facettesY), 0.5);
            glVertex3f(-0.5 + (i + 1) * (1.0 / facettesX), -0.5 + j * (1.0 / facettesY), 0.5);
            glEnd();

            glBegin(GL_QUADS);
            glNormal3f(0.0, 0.0, -1.0);
            glVertex3f(-0.5 + i * (1.0 / facettesX), -0.5 + j * (1.0 / facettesY), -0.5);
            glVertex3f(-0.5 + i * (1.0 / facettesX), -0.5 + (j + 1) * (1.0 / facettesY), -0.5);
            glVertex3f(-0.5 + (i + 1) * (1.0 / facettesX), -0.5 + (j + 1) * (1.0 / facettesY), -0.5);
            glVertex3f(-0.5 + (i + 1) * (1.0 / facettesX), -0.5 + j * (1.0 / facettesY), -0.5);
            glEnd();
        }
    }

    glPopMatrix();
}

void Wall::render()
{
    glPushMatrix();
    glTranslatef(posX, height / 2, posZ);
    glRotatef(rotation, 0, 1, 0);

    glScalef(width, height, thickness);

    drawCube(10, 10);
    glPopMatrix();
}