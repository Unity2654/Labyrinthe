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

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
    texture.bind();
    glFrontFace(GL_CW);
    glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    glEnable(GL_TEXTURE_GEN_T);

    glutSolidSphere(1,50,50);

    glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    glDisable(GL_TEXTURE_GEN_T);
    glFrontFace(GL_CCW);
}

void Sky::render(){
    glPushMatrix();
    glTranslatef(0, positionY*1.5, 0);
    glScalef(sizeX*1.3, sizeY*1.5, sizeZ*1.3);

    drawSky(50, 50);
    glPopMatrix();
}
