#include "Character.h"

Character::Character(float px, float py, float pz, gloop::Camera &cam, gloop::PonctualLight &poncLight, gloop::SpotLight &spotLight) : pos(px,py,pz), speed(0, 0, 0), cam(px, py, pz), PonctualLight::PonctualLight(){
    speed = gloop::Vector3f(0, 0, 0);
    cam = cam;
    poncLight = poncLight;
    spotLight = spotLight;

}