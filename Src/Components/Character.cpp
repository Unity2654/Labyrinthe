#include "Character.h"
#include <cmath>
#include "../GlOOPLib/Physics/Physics.h"
#include "LabyrintheScene.h"
#include "../GlOOPLib/Maths/Utils.h"
#include "../GlOOPLib/PropertyManager/GlPropertyManager.h"

#define MOVEMENT_SPEED 0.05f
#define SPRINT_SPEED 0.05f
#define GRAVITY 0.01f
#define JUMP_FORCE 0.2f
#if defined(WIN32) || defined(WIN64)
#define MOUSE_SENS 0.0015f
#else
#define MOUSE_SENS 0.006f
#endif

#define SPECIAL_KEY_OFFSET 256 

Character::Character(gloop::Vector3f pos) :
    pos(pos),
    jump(0.0f),
    isSprinting(false),
    rotate_x(0.0f),
    rotate_y(0.0f),
    looking_at(0.0f, 0.0f, -1.0f),
    camFP(pos, pos + looking_at, { 0.0f, 1.0f, 0.0f }, 120.0f, 1.0f, 0.1f, 100.0f),
    camMap({ pos.x, pos.y + 30.0f, pos.z }, pos, { 0.0f, 0.0f, -1.0f }, -10, 10, -10, 10, 0.1f, 100.0f),
    fp(true),
    speed(0.0f,0.0f){
    for (int i = 0; i < 4; i++){
        moving[i] = 0;
    }
    // prop::getSceneManager().getActiveScene<LabyrintheScene&>().addDynamicLight(&light);
}

void Character::update(){

    updateMouse();
    updateMovement();
    // updateLight();


    auto& d = prop::getDisplay();
    double ratio = (float)d.getSizeX() / d.getSizeY();

    camFP.pos = pos;
    camFP.ori = pos + looking_at;
    camFP.reshape(120.0f, ratio);

    camMap.pos = { pos.x, pos.y + 30.0f, pos.z };
    camMap.ori = pos;
    camMap.reshape(-10.0*ratio, 10.0*ratio, -10.0f, 10.0f);
}

void Character::render()
{
    if (fp){
        camFP.buildPerspectiveCamera();
    }else{
        camMap.buildOrthoCamera();

        renderOnMap(1.0f);
    }
    updateLight();
    //drawHitbox(3.0f);
}

void Character::renderOnMap(float scale){
    double direction = (looking_at.x < 0?-1:1) * gloop::radToDeg(acos(looking_at.dot(gloop::Vector3f{ 0.0, 0.0, 1.0 }) / looking_at.norm()));

    glPushMatrix();
    glTranslatef(pos.x, 2.0f, pos.z);
    glRotatef(direction, 0.0f,1.0f,0.0f);
    glScalef(scale, scale, scale);
    glBegin(GL_TRIANGLES);
    glVertex3f(0.4f, 0.0f, -0.5f);
    glVertex3f(-0.4f, 0.0f, -0.5f);
    glVertex3f(0.0f, 0.0f ,0.5f);
    glEnd();
    glPopMatrix();
}

void Character::updateMovement(){

    auto& key = prop::getKey();

    moving[0] = key.getKeyState('z') || key.getKeyState(SPECIAL_KEY_OFFSET + GLUT_KEY_UP);
    moving[1] = key.getKeyState('s') || key.getKeyState(SPECIAL_KEY_OFFSET + GLUT_KEY_DOWN);
    moving[2] = key.getKeyState('q') || key.getKeyState(SPECIAL_KEY_OFFSET + GLUT_KEY_LEFT);
    moving[3] = key.getKeyState('d') || key.getKeyState(SPECIAL_KEY_OFFSET + GLUT_KEY_RIGHT);

    isSprinting = key.getKeyState('a');

    if (key.getKeyState(' ') && pos.y <= 1.75f){
        Jump();
    }

    gloop::Vector2f vect{ looking_at.x, looking_at.z };
    speed = { 0.0f,0.0f };

    if (moving[0]) { speed.x += vect.x; speed.y += vect.y; }
    if (moving[1]) { speed.x -= vect.x; speed.y -= vect.y; }
    if (moving[2]) { speed.x += vect.y; speed.y -= vect.x; }
    if (moving[3]) { speed.x -= vect.y; speed.y += vect.x; }

    speed = speed.normalize() * (MOVEMENT_SPEED + isSprinting * SPRINT_SPEED);
    auto& otherObjects = prop::getSceneManager().getActiveScene<LabyrintheScene&>().getNearbyHitboxes(pos);
    gloop::collisionData data = gloop::Physics::collide(getCollisionBox(), otherObjects);

    speed = speed + data.collision;

    pos.x += speed.x + data.correction.x;
    pos.z += speed.y + data.correction.y;

    if (jump > 0.0f || pos.y > 1.75f){
        pos.y += jump;
        jump -= GRAVITY;
    }
    else{
        jump = 0.0f;
        pos.y = 1.75f;
    }
}

void Character::Jump(){
    if (pos.y <= 1.75f){
        jump = JUMP_FORCE;
    }
        
}

void Character::switchCamera(){
    fp = !fp;
}

bool Character::isFirstPerson() const{
    return fp;
}

gloop::Vector3f Character::getPosition() const{
    return pos;
}

void Character::setLookingAt(const gloop::Vector3f& dir) {
    looking_at = dir;
}

void Character::updateMouse()
{
    gloop::Vector2f center = prop::getDisplay().getCenter();
    auto mouseDep = prop::getMouse().getMovement() * MOUSE_SENS;


    rotate_x += mouseDep.x;
    rotate_y += mouseDep.y;

    const float limit = 1.5f;
    if (rotate_y > limit) rotate_y = limit;
    if (rotate_y < -limit) rotate_y = -limit;

    looking_at.x = cos(rotate_y) * sin(rotate_x);
    if(fp)
        looking_at.y = -sin(rotate_y);
    looking_at.z = -cos(rotate_y) * cos(rotate_x);
}

gloop::CollisionBox Character::getCollisionBox() const{
    return gloop::CollisionBox{
        gloop::Rectangle::fromCenter({pos.x, pos.z}, 1, 1),
        true,
        {},
        { speed.x, speed.y }
    };
}

void Character::updateLight() {
    lightWhite.position = pos;
    lightYellow.position = pos;
    lightOrange.position = pos;
    lightRed.position = pos;
    lightWhite.render();
    lightYellow.render();
    lightOrange.render();
    lightRed.render();
}

Character::~Character() {
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHT2);
    glDisable(GL_LIGHT3);
}