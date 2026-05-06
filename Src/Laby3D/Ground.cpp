#include "Ground.h"

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "../GlOOPLib/PropertyManager/GlPropertyManager.h"

Ground::Ground(float sizeX, float sizeZ) : sizeX(sizeX), sizeZ(sizeZ), texture(gloop::TextureManager::load("../Resources/ground.png")){
}

void Ground::drawCube(int facettesX, int facettesZ)
{
    float white[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
    
    texture.bind();
    glNormal3f(0.0, 1.0, 0.0);

    float sizeFacettesX = 1.0 / facettesX;
    float sizeFacettesZ = 1.0 / facettesZ;
    for (int i = 0; i <= facettesZ; i++)
    {
        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= facettesX; j++)
        {
            glTexCoord2f(j * sizeFacettesX, i * sizeFacettesZ);
            glVertex3f(-0.5 + j * sizeFacettesX, 0.5, -0.5 + i * sizeFacettesZ);
            glTexCoord2f(j * sizeFacettesX, (i+1) * sizeFacettesZ);
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

    int f = prop::getFacets();
    drawCube(f * 5, f * 5); 

    glPopMatrix();
}