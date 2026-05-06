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

    // Horizontal wall (ceilling)
    glBegin(GL_QUADS);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, 0.5f, -0.5f);

    glEnd();
}

void Sky::render(){
    glPushMatrix();
    glTranslatef(0, positionY, 0);
    glScalef(sizeX, 0.2, sizeZ);

    drawSky(50, 50);
    glPopMatrix();
}
