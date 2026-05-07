#include "Wall.h"
#include "GL/glut.h"
#include "GL/gl.h"
#include "GL/glu.h"
#include <iostream>
#include "../GlOOPLib/Maths/Utils.h"
#include "../GlOOPLib/Textures/Texture.h"
#include "../GlOOPLib/PropertyManager/GlPropertyManager.h"

//#define SHOW_HITBOX

Wall::Wall(float posX, float posZ, float width, float thickness, float height, float rotation) : 
    posX(posX), 
    posZ(posZ), 
    width(width), 
    thickness(thickness), 
    height(height), 
    rotation(rotation),
    hitbox{ gloop::Rectangle::fromCenter(
        { posX, posZ },
        width * cos(gloop::degToRad(rotation)) + thickness * sin(gloop::degToRad(rotation)),
        width * sin(gloop::degToRad(rotation)) + thickness * cos(gloop::degToRad(rotation)))
    },
    texture(gloop::TextureManager::load("../Resources/walls.png")) {
}

void Wall::drawCube(int facettesX, int facettesY) const
{
    glPushMatrix();

    texture.bind();

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
            double ratioX = 1.0 / facettesX;
            double ratioY = 1.0 / facettesY;
            //glBegin(GL_QUADS);
            glNormal3f(0.0, 0.0, 1.0);
            glTexCoord2f((i+1)*ratioX, j*ratioY);
            glVertex3f(-0.5 + (i + 1) * ratioX, -0.5 + j * ratioY, 0.5);
            glTexCoord2f((i + 1) * ratioX, (j+1) * ratioY);
            glVertex3f(-0.5 + (i + 1) * ratioX, -0.5 + (j + 1) * ratioY, 0.5);
            glTexCoord2f(i * ratioX, (j + 1) * ratioY);
            glVertex3f(-0.5 + i * ratioX, -0.5 + (j + 1) * ratioY, 0.5);
            glTexCoord2f(i * ratioX, j * ratioY);
            glVertex3f(-0.5 + i * ratioX, -0.5 + j * ratioY, 0.5);
            //glEnd();

            //glBegin(GL_QUADS);
            glNormal3f(0.0, 0.0, -1.0);
            glTexCoord2f(i * ratioX, j * ratioY);
            glVertex3f(-0.5 + i * ratioX, -0.5 + j * ratioY, -0.5);
            glTexCoord2f(i * ratioX, (j + 1) * ratioY);
            glVertex3f(-0.5 + i * ratioX, -0.5 + (j + 1) * ratioY, -0.5);
            glTexCoord2f((i+1) * ratioX, (j + 1) * ratioY);
            glVertex3f(-0.5 + (i + 1) * ratioX, -0.5 + (j + 1) * ratioY, -0.5);
            glTexCoord2f((i+1) * ratioX, j * ratioY);
            glVertex3f(-0.5 + (i + 1) * ratioX, -0.5 + j * ratioY, -0.5);
            //glEnd();
        }
    }
    glEnd();
    glPopMatrix();
}

void Wall::render()
{
    displayMaterial.apply(GL_FRONT_AND_BACK);
#ifdef SHOW_HITBOX
    Collidable::drawHitbox(height);
#else
    glPushMatrix();
    glTranslatef(posX, height / 2, posZ);
    glRotatef(rotation, 0, 1, 0);

    glScalef(width, height, thickness);

    int f = prop::getFacets();
    drawCube(f, f);
    glPopMatrix();
#endif
}

gloop::CollisionBox Wall::getCollisionBox() const{
    return hitbox;
}