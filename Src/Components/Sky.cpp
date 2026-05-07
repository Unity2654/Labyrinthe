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


static void drawSphere(float r, float spaceX, float spaceY) {
    float PI = 3.14159;
    glPushMatrix();
    glRotatef(90, -1, 0, 0);
    glBegin(GL_QUAD_STRIP);

    float texX = 0;
    float texY = 0;
    float texSpace = 1;
    // First side of the sphere
    for (float b = 0; b <= 90 - spaceY; b += spaceY) {
        for (float a = 0; a <= 360 - spaceX; a += spaceX) {
            glTexCoord2f(texX, texY);
            glVertex3f(
                r * sin((a) / 180 * PI) * sin((b) / 180 * PI),
                r * cos((a) / 180 * PI) * sin((b) / 180 * PI),
                r * cos((b) / 180 * PI)
            );

            glTexCoord2f(texX, texY+texSpace);
            glVertex3f(
                r * sin((a) / 180 * PI) * sin((b+spaceY) / 180 * PI),
                r * cos((a) / 180 * PI) * sin((b+spaceY) / 180 * PI),
                r * cos((b+spaceY) / 180 * PI)
            );

            glTexCoord2f(texX+texSpace, texY);
            glVertex3f(
                r * sin((a+spaceX) / 180 * PI) * sin((b) / 180 * PI),
                r * cos((a+spaceX) / 180 * PI) * sin((b) / 180 * PI),
                r * cos((b) / 180 * PI)
            );

            glTexCoord2f(texX+texSpace, texY+texSpace);
            glVertex3f(
                r * sin((a + spaceX) / 180 * PI) * sin((b + spaceY) / 180 * PI),
                r * cos((a + spaceX) / 180 * PI) * sin((b + spaceY) / 180 * PI),
                r * cos((b + spaceX) / 180 * PI)
            );
            texX += texSpace;
            texY += texSpace;
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

    drawSphere(1, 5, 5);

}

void Sky::render(){
    glPushMatrix();
    glScalef(sizeX*1.5, sizeY*2, sizeZ*1.5);

    drawSky(50, 50);
    glPopMatrix();
}
