#include "Wall.h"
#include "GL/glut.h"
#include "GL/gl.h"
#include "GL/glu.h"
#include <stdlib.h>

Wall::Wall(float posX, float posZ, float width, float thickness, float height, float rotation) : posX(posX), posZ(posZ), width(width), thickness(thickness), height(height), rotation(rotation)
{
}

void Wall::drawCube(int facettesX, int facettesY) const
{
    displayMaterial.apply(GL_FRONT_AND_BACK);
    glPushMatrix();

    glBegin(GL_QUADS);
    for (int i = 0; i < facettesX; i++)
    {
        //glBegin(GL_QUADS);
        glNormal3f(0.0, 1.0, 0.0);
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(0.5, 0.5, -0.5);
        glVertex3f(-0.5, 0.5, -0.5);
        glVertex3f(-0.5, 0.5, 0.5);
        //glEnd();

        for (int j = 0; j < facettesY; j++)
        {
            //glBegin(GL_QUADS);
            glNormal3f(0.0, 0.0, 1.0);
            glVertex3f(-0.5 + i * (1.0 / facettesX), -0.5 + j * (1.0 / facettesY), 0.5);
            glVertex3f(-0.5 + i * (1.0 / facettesX), -0.5 + (j + 1) * (1.0 / facettesY), 0.5);
            glVertex3f(-0.5 + (i + 1) * (1.0 / facettesX), -0.5 + (j + 1) * (1.0 / facettesY), 0.5);
            glVertex3f(-0.5 + (i + 1) * (1.0 / facettesX), -0.5 + j * (1.0 / facettesY), 0.5);
            //glEnd();

            //glBegin(GL_QUADS);
            glNormal3f(0.0, 0.0, -1.0);
            glVertex3f(-0.5 + i * (1.0 / facettesX), -0.5 + j * (1.0 / facettesY), -0.5);
            glVertex3f(-0.5 + i * (1.0 / facettesX), -0.5 + (j + 1) * (1.0 / facettesY), -0.5);
            glVertex3f(-0.5 + (i + 1) * (1.0 / facettesX), -0.5 + (j + 1) * (1.0 / facettesY), -0.5);
            glVertex3f(-0.5 + (i + 1) * (1.0 / facettesX), -0.5 + j * (1.0 / facettesY), -0.5);
            //glEnd();
        }
    }
    glEnd();

#ifdef SHOW_HITBOX // Show hitbox for debug purposes
    drawHitbox();
#endif

    glPopMatrix();
}

void Wall::drawHitbox() const{
    int polygonMode;
    glGetIntegerv(GL_POLYGON_MODE, &polygonMode);
    glPolygonMode(GL_FRONT, GL_LINE);

    glBegin(GL_QUADS);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, 0.5);

    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(-0.5, -0.5, 0.5);

    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);

    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);

    glEnd();
    glPolygonMode(GL_FRONT, polygonMode);
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

gloop::Rectangle Wall::getCollisionBox() const{
    return gloop::Rectangle::fromCenter({posX, posZ}, width, thickness);
}
