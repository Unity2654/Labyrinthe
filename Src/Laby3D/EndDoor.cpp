#include "EndDoor.h"
#include "../GlOOPLib/Maths/Utils.h"
#include "../GlOOPLib/Textures/Texture.h"
#include "../GlOOPLib/Maths/Vector.h"
#include "EndDoorParticle.h"
#include "GL/gl.h"
#include "GL/glu.h"
#include "GL/glut.h"

EndDoor::EndDoor(float posX, float posZ, float height, float width, float rotation, gloop::Scene &scene) :
    posX(posX),
    posZ(posZ),
    height(height),
    width(width),
    rotation(rotation),
    hitbox{ gloop::Rectangle::fromCenter(
        { posX, posZ },
        1.0f, 1.0f)
    },
    texture(gloop::TextureManager::load("../Resources/portal.png")),
    scene(scene)
{
    srand(static_cast<unsigned>(time(nullptr)));
    for (int i = 0; i < 30; i++) {

        float offsetY = (rand() % 100) / 100.0f * ((height>width?width:height)/2);
        float offsetZ = (rand() % 100) / 100.0f * 0.5f + 0.3f;
        float velocity = (rand() % 100) / 100.0f * 4.0f + 0.5f;
        float rotationSpeed = (rand() % 100) / 100.0f * 2.0f + 0.5f;
        float size = (rand() % 100) / 100.0f * 0.05f + 0.01f;

        scene.addEntity(EndDoorParticle(offsetY, offsetZ, velocity, rotationSpeed, size, gloop::Vector3f(posX, height/2, posZ), rotation));
    }
}

void EndDoor::drawCube()  {
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);

    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);

    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);

    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f , 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);

    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);

    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glEnd();
}

void EndDoor::render() {

    texture.bind();

    glPushMatrix();
    glTranslatef(posX, 0.0f, posZ);
    glRotatef(rotation, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, 0.11f);


    


    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    float white[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
    gloop::Vector2f points[] =
    {
        // { -0.3635f, 0.0f },
        // { 0.3635f, 0.0f },
        // { 0.386f, 0.20f },
        // { 0.4545f, 0.37f },
        // { 0.3635f, 0.59f },
        // { 0.295f, 0.83f },
        // { 0.1135f, 0.96f },
        // { -0.1135f, 1.00f },
        // { -0.3405f, 0.93f },
        // { -0.4545f, 0.77f },
        // { -0.5f, 0.53f },
        // { -0.477f, 0.29f }

        // { -0.5f, 0.0f },
        // { 0.5f, 0.0f },
        // { 0.5f, 1.0f },
        // { -0.5f, 1.0f }

        { -0.4f, 0.0f },
        { 0.4f, 0.0f },
        { 0.5f, 0.8f },
        { 0.3f, 1.0f },
        { -0.3f, 1.0f },
        { -0.5f, 0.8f },


    };

    int nbPoints = 6;

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, 1.0f);
    for (const gloop::Vector2f& point : points) {
        glTexCoord2f((point.x + 0.5f) / width, point.y);
        glVertex3f(point.x * width, point.y * height, 0.0f);
    }
    glEnd();

    float gold[] = {0.9f, 0.9f, 0.9f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, gold);
    for(int i = 0; i < nbPoints; i++){
        // brique sur le cote
        gloop::Vector2f milieu = { (points[i].x + points[(i + 1) % nbPoints].x) / 2, (points[i].y + points[(i + 1) % nbPoints].y) / 2 };
        glPushMatrix();
        glTranslatef(milieu.x * width, milieu.y * height, 0.0f);
        float angle = atan2(points[(i + 1) % nbPoints].y - points[i].y, points[(i + 1) % nbPoints].x - points[i].x) * 180 / M_PI;
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
        glScalef(0.1+sqrt(0.1+
            ((points[(i + 1) % nbPoints].y - points[i].y)*height) * ((points[(i + 1) % nbPoints].y - points[i].y)*height) + 
            ((points[(i + 1) % nbPoints].x - points[i].x)*width) * ((points[(i + 1) % nbPoints].x - points[i].x)*width)
        ), 0.15f, 0.15f);
        drawCube();
        glPopMatrix();
    }


    //light
    float lightPos[] = {0.0f, height/2, 0.2f, 1.0f};
    glLightfv(GL_LIGHT7, GL_POSITION, lightPos);
    float lightColor[] = {1.0f, 0.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT7, GL_DIFFUSE, lightColor);
    // attenuation
    glLightf(GL_LIGHT7, GL_LINEAR_ATTENUATION, 0.2f);
    glLightf(GL_LIGHT7, GL_QUADRATIC_ATTENUATION, 0.03f);
    glEnable(GL_LIGHT7);
    




    glPopMatrix();
}



gloop::CollisionBox EndDoor::getCollisionBox() const {
    return hitbox;
}