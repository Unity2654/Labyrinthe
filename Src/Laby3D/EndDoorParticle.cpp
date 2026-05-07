#include "EndDoorParticle.h"
#include "GL/glu.h"
#include "GL/glut.h"
#include <cmath>

EndDoorParticle::EndDoorParticle(float offsetY, float offsetZ, float velocity, float rotationSpeed, float size, gloop::Vector3f initialPosition, int rotation) : 
    offsetY(offsetY), 
    offsetZ(offsetZ), 
    velocity(velocity), 
    rotationSpeed(rotationSpeed),
    size(size),
    initialPosition(initialPosition),
    alpha(0),
    rotation(rotation)
{
}

void EndDoorParticle::update() {
    alpha ++;
}

void EndDoorParticle::render() {


    glPushMatrix();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTranslatef(initialPosition.x, initialPosition.y, initialPosition.z);
    glRotatef(rotation, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, offsetZ);
    glRotatef(alpha * velocity, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, offsetY, 0.0f);
    glRotatef(alpha*rotationSpeed, 0.0f, 0.0f, 1.0f);
    glRotatef(alpha*rotationSpeed, 0.0f, 1.0f, 0.0f);
    glRotatef(alpha*rotationSpeed, 1.0f, 1.0f, 0.0f);

    
    float color[] = {0.94f, 0.24f, 1.0f, 0.2f + 0.8f * ((sin(alpha*0.01f*rotationSpeed)+1)/2)};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
    float scaledSize = size + sin(alpha*0.1f+size)*0.02f;
    glScalef(scaledSize, scaledSize, scaledSize);
    glutSolidIcosahedron();
    glDisable(GL_BLEND);
    glPopMatrix();
}
