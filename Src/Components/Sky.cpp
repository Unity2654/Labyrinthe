#include "Sky.h"
#include <GL/gl.h>

Sky::Sky(float sizeX, float sizeZ, float sizeY, float positionY) :
    sizeX(sizeX),
    sizeZ(sizeZ),
    sizeY(sizeY),
	positionY(positionY),
	texture(gloop::TextureManager::load("../Resources/sky.png")){}

void Sky::drawSky(int facettesX, int facettesZ){
    float white[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);

    texture.bind();
    glNormal3f(0.0, -1.0, 0.0);

    float sizeFacettesX = 1.0 / facettesX;
    float sizeFacettesZ = 1.0 / facettesZ;
    glBegin(GL_QUADS);
    for (int i = 0; i <= facettesZ; i++)
    {
        for (int j = 0; j <= facettesX; j++)
        {
            // Horizontal wall
            glTexCoord2f(j * sizeFacettesX, (i + 1) * sizeFacettesZ);
            glVertex3f(-0.5 + j * sizeFacettesX, 0.5, -0.5 + (i + 1) * sizeFacettesZ);
            glTexCoord2f(j * sizeFacettesX, i * sizeFacettesZ);
            glVertex3f(-0.5 + j * sizeFacettesX, 0.5, -0.5 + i * sizeFacettesZ);
            glTexCoord2f((j+1) * sizeFacettesX, i * sizeFacettesZ);
            glVertex3f(-0.5 + (j+1) * sizeFacettesX, 0.5, -0.5 + i * sizeFacettesZ);
            glTexCoord2f((j+1) * sizeFacettesX, (i+1) * sizeFacettesZ);
            glVertex3f(-0.5 + (j+1) * sizeFacettesX, 0.5, -0.5 + (i+1) * sizeFacettesZ);
        }
    }
    glEnd();
}

void Sky::render(){
    glPushMatrix();
    glTranslatef(0, positionY, 0);
    glScalef(sizeX, 0.2, sizeZ);

    drawSky(50, 50);
    glPopMatrix();
}
