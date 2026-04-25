#include "Pillar.h"

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

//#define SHOW_HITBOX

void Pillar::drawCube(int facettesX, int facettesY, float height)  const{ 
    double ratioX = 1.0 / facettesX;
    double ratioY = height / facettesY;
    double h = height / 2;

    glPushMatrix();

    texture.bind();
    glBegin(GL_QUADS);
    for (int i = 0; i < facettesX; i++)
    {
        //glBegin(GL_QUADS);
        glNormal3f(0.0, 1.0, 0.0);
        glVertex3f(0.5, h, 0.5);
        glVertex3f(0.5, h, -0.5);
        glVertex3f(-0.5, h, -0.5);
        glVertex3f(-0.5, h, 0.5);

        glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(-0.5, -h, 0.5);
        glVertex3f(-0.5, -h, -0.5);
        glVertex3f(0.5, -h, -0.5);
        glVertex3f(0.5, -h, 0.5);
        //glEnd();

        for (int j = 0; j < facettesY; j++){

            glNormal3f(0.0, 0.0, 1.0);
            glTexCoord2f((i + 1) * ratioX, j * ratioY);
            glVertex3f(-0.5 + (i + 1) * ratioX, -h + j * ratioY, 0.5);
            glTexCoord2f((i + 1) * ratioX, (j + 1) * ratioY);
            glVertex3f(-0.5 + (i + 1) * ratioX, -h + (j + 1) * ratioY, 0.5);
            glTexCoord2f(i * ratioX, (j + 1) * ratioY);
            glVertex3f(-0.5 + i * ratioX, -h + (j + 1) * ratioY, 0.5);
            glTexCoord2f(i * ratioX, j * ratioY);
            glVertex3f(-0.5 + i * ratioX, -h + j * ratioY, 0.5);

            glNormal3f(0.0, 0.0, -1.0);
            glTexCoord2f(i * ratioX, j * ratioY);
            glVertex3f(-0.5 + i * ratioX, -h + j * ratioY, -0.5);
            glTexCoord2f(i * ratioX, (j + 1) * ratioY);
            glVertex3f(-0.5 + i * ratioX, -h + (j + 1) * ratioY, -0.5);
            glTexCoord2f((i + 1) * ratioX, (j + 1) * ratioY);
            glVertex3f(-0.5 + (i + 1) * ratioX, -h + (j + 1) * ratioY, -0.5);
            glTexCoord2f((i + 1) * ratioX, j * ratioY);
            glVertex3f(-0.5 + (i + 1) * ratioX, -h + j * ratioY, -0.5);

            glNormal3f(-1.0, 0.0, 0.0);
            glTexCoord2f((i + 1) * ratioX, j * ratioY);
            glVertex3f(-0.5, -h + j * ratioY, -0.5 + (i + 1) * ratioX);
            glTexCoord2f((i + 1) * ratioX, (j + 1) * ratioY);
            glVertex3f(-0.5, -h + (j + 1) * ratioY, -0.5 + (i + 1) * ratioX);
            glTexCoord2f(i * ratioX, (j + 1) * ratioY);
            glVertex3f(-0.5, -h + (j + 1) * ratioY, -0.5 + i * ratioX);
            glTexCoord2f(i * ratioX, j * ratioY);
            glVertex3f(-0.5, -h + j * ratioY, -0.5 + i * ratioX);
            
            glNormal3f(1.0, 0.0, 0.0);
            glTexCoord2f(i * ratioX, j * ratioY);
            glVertex3f(0.5, -h + j * ratioY, -0.5 + i * ratioX);
            glTexCoord2f(i * ratioX, (j + 1) * ratioY);
            glVertex3f(0.5, -h + (j + 1) * ratioY, -0.5 + i * ratioX);
            glTexCoord2f((i + 1) * ratioX, (j + 1) * ratioY);
            glVertex3f(0.5, -h + (j + 1) * ratioY, -0.5 + (i + 1) * ratioX);
            glTexCoord2f((i + 1) * ratioX, j * ratioY);
            glVertex3f(0.5, -h + j * ratioY, -0.5 + (i + 1) * ratioX);
        }
    }
    glEnd();
    glPopMatrix();
}

Pillar::Pillar(float posX, float posZ, float thickness, float height) : posX(posX), posZ(posZ), thickness(thickness), height(height), texture(gloop::TextureManager::load("../Resources/pillars.png"))
{
}

void Pillar::render()
{
    displayMaterial.apply(GL_FRONT_AND_BACK);
#ifdef SHOW_HITBOX // Show hitbox for debug purposes
    Collidable::drawHitbox(height);
#else
    glPushMatrix();
    glTranslatef(posX, height/2, posZ);
    glScalef(thickness, 1.0, thickness);
    drawCube(10, 10, height*0.8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(posX, height/20, posZ);
    glScalef(thickness * 1.2, 1.0, thickness * 1.2);
    drawCube(1, 1, height / 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(posX, height - height/20, posZ);
    glScalef(thickness * 1.2, 1.0, thickness * 1.2);
    drawCube(2, 2, height/10);
    glPopMatrix();
#endif
}

gloop::CollisionBox Pillar::getCollisionBox() const{
    return { gloop::Rectangle::fromCenter({ posX, posZ }, thickness, thickness) };
}