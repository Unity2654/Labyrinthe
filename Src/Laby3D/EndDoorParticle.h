#pragma once
#include "../GlOOPLib/Objects/Entity3D.h"
#include "../GlOOPLib/Maths/Vector.h"


class EndDoorParticle : public gloop::Entity3D
{ 
    private:
        float offsetY;
        float offsetZ;
        float velocity;
        float rotationSpeed;
        float size;
        int alpha;
        int rotation;
        gloop::Vector3f initialPosition;
    
    public:
        EndDoorParticle(float offsetY, float offsetZ, float velocity, float rotationSpeed, float size, gloop::Vector3f initialPosition, int rotation);
        void update();
        void render();
};