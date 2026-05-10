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
        /**
         * @brief Construct a new End Door Particle object
         * @param offsetY The initial Y offset of the particle from the center of the door
         * @param offsetZ The initial Z offset of the particle from the center of the door
         * @param velocity The velocity at which the particle moves in circle
         * @param rotationSpeed The speed at which the particle rotates on itself
         * @param size The size of the particle
         * @param initialPosition The initial position of the particle, used to calculate its movement (the position of the center of the door)
         * @param rotation The rotation of the door, used to calculate the initial position of the particle
         */
        EndDoorParticle(float offsetY, float offsetZ, float velocity, float rotationSpeed, float size, gloop::Vector3f initialPosition, int rotation);

        /**
         * @brief Updates the particle, move it in circle and make it fade out
         */
        void update();

        /**
         * @brief Renders the particle
         */
        void render();
};