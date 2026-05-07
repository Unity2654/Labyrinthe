#include "Sky.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include "../GlOOPLib/Lights/Materials.h"

Sky::Sky(float sizeX, float sizeZ, float sizeY, float positionY) :
    sizeX(sizeX),
    sizeZ(sizeZ),
    sizeY(sizeY),
	positionY(positionY),
	texture(gloop::TextureManager::load("../Resources/sky.png")){}


void drawSphere(float r, float spaceX, float spaceY) {
    float PI = 3.14159;
    glPushMatrix();
    glRotatef(90, -1, 0, 0);
    glBegin(GL_QUAD_STRIP);
    // First side of the sphere
    for (float b = 0; b <= 90 - spaceY; b += spaceY) {
        for (float a = 0; a <= 360 - spaceX; a += spaceX) {
            glTexCoord2f((a) / 360, (2 * b) / 360);
            glVertex3f(
                r * sin((a) / 180 * PI) * sin((b) / 180 * PI),
                r * cos((a) / 180 * PI) * sin((b) / 180 * PI),
                r * cos((b) / 180 * PI)
            );

            glTexCoord2f((a) / 360, (2 * (b+spaceY)) / 360);
            glVertex3f(
                r * sin((a) / 180 * PI) * sin((b+spaceY) / 180 * PI),
                r * cos((a) / 180 * PI) * sin((b+spaceY) / 180 * PI),
                r * cos((b+spaceY) / 180 * PI)
            );

            glTexCoord2f((a+spaceX) / 360, (2 * b) / 360);
            glVertex3f(
                r * sin((a+spaceX) / 180 * PI) * sin((b) / 180 * PI),
                r * cos((a+spaceX) / 180 * PI) * sin((b) / 180 * PI),
                r * cos((b) / 180 * PI)
            );

            glTexCoord2f((a + spaceX) / 360, (2 * b + spaceY) / 360);
            glVertex3f(
                r * sin((a + spaceX) / 180 * PI) * sin((b + spaceY) / 180 * PI),
                r * cos((a + spaceX) / 180 * PI) * sin((b + spaceY) / 180 * PI),
                r * cos((b + spaceX) / 180 * PI)
            );
        }
    }
    glEnd();
    glPopMatrix();
}


void Sky::drawSky(int facettesX, int facettesZ){
    //gloop::Material
    auto& mat = gloop::Material{
        { 0.0f,0.0f,0.0f,1.0f },
        { 0.0f,0.0f,0.0f,1.0f },
        { 0.0f,0.0f,0.0f,1.0f },
        { 0.5f,0.5f,0.5f,1.0f }
    };
    mat.apply(GL_FRONT);

    texture.bind();
    //glFrontFace(GL_CW);
    //glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    //glEnable(GL_TEXTURE_GEN_T);

    drawSphere(1, 5, 5);

    //glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    //glDisable(GL_TEXTURE_GEN_T);
    //glFrontFace(GL_CCW);
}

void Sky::render(){
    glPushMatrix();
    //glTranslatef(0, positionY*1.5, 0);
    glScalef(sizeX*1.5, sizeY*2, sizeZ*1.5);

    drawSky(50, 50);
    glPopMatrix();
}
