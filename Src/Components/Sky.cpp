#include "Sky.h"
#include <GL/gl.h>
#include <GL/glut.h>

Sky::Sky(float sizeX, float sizeZ, float sizeY, float positionY) :
    sizeX(sizeX),
    sizeZ(sizeZ),
    sizeY(sizeY),
	positionY(positionY),
	texture(gloop::TextureManager::load("../Resources/sky.png")){}

void Sky::drawSky(int facettesX, int facettesZ){
    float white[] = { 1.0, 1.0, 1.0, 1.0 };

    glFrontFace(GL_CW);
    glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    glEnable(GL_TEXTURE_GEN_T);

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
    texture.bind();
    glutSolidCube(1.0f);

    glFrontFace(GL_CCW);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
}

void Sky::render(){
    glPushMatrix();
    glTranslatef(0, positionY, 0);
    glScalef(sizeX*2, sizeY*2, sizeZ*2);

    drawSky(50, 50);
    glPopMatrix();
}
