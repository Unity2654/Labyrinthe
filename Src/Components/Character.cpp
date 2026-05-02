#include "Character.h"
#include <cmath>
#include "../GlOOPLib/Physics/Physics.h"
#include "LabyrintheScene.h"


#define MOVEMENT_SPEED 0.05f
#define SPRINT_SPEED 0.05f
#define GRAVITY 0.01f
#define JUMP_FORCE 0.2f
#define MOUSE_SENS 0.006f

#define SPECIAL_KEY_OFFSET 256 

Character::Character(gloop::Vector3f pos) :
    pos(pos),
    jump(0.0f),
    isSprinting(false),
    rotate_x(0.0f),
    rotate_y(0.0f),
    looking_at(0.0f, 0.0f, -1.0f),
    camFP(pos, pos + looking_at, { 0.0f, 1.0f, 0.0f }, 60.0f, 1.0f, 0.1f, 100.0f),
    camMap({ pos.x, pos.y + 20.0f, pos.z }, pos, { 0.0f, 0.0f, -1.0f }, -10, 10, -10, 10, 0.1f, 100.0f),
    fp(true),
    speed(0.0f,0.0f){
    for (int i = 0; i < 4; i++){
        moving[i] = 0;
    }
}

void Character::update(){
    updateMouse();
    updateMovement();

    auto& d = prop::getDisplay();

    camFP.pos = pos;
    camFP.ori = pos + looking_at;
    camFP.reshape(d.getSizeX(), d.getSizeX() / d.getSizeY());

    camMap.pos = { pos.x, pos.y + 20.0f, pos.z };
    camMap.ori = pos;
    camMap.reshape(-d.getSizeX()/2, d.getSizeX() / 2, -d.getSizeY() / 2, d.getSizeY() / 2);
}

void Character::render()
{
    if (fp){
        camFP.buildPerspectiveCamera();
    }else{
        camMap.buildOrthoCamera();
    }
    //drawHitbox(3.0f);
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
    auto center = prop::getDisplay().getCenter();
    auto mouseDep = (prop::getMouse().getPosition() - center) * MOUSE_SENS;


    rotate_x += mouseDep.x;
    rotate_y += mouseDep.y;

    const float limit = 1.5f;
    if (rotate_y > limit) rotate_y = limit;
    if (rotate_y < -limit) rotate_y = -limit;

    looking_at.x = cos(rotate_y) * sin(rotate_x);
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
