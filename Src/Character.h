#pragma once

#include "GlOOPLib/Objects/Entity3D.h"
#include "GlOOPLib/Camera/Camera.h"
#include "GlOOPLib/Maths/Vector.h"
#include "GlOOPLib/Lights/Lights.h"


class Character : public gloop::Entity3D{
public :

    gloop::Vector3f pos;
    gloop::Vector3f speed;
    gloop::Camera cam;
    gloop::PonctualLight poncLight;
    gloop::SpotLight spotLight;
    //forme du perso??

    Character::Character(float px, float py, float pz, gloop::Camera &cam, gloop::PonctualLight &poncLight, gloop::SpotLight &spotLight);

};