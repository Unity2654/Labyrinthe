#include "Physics.h"
#include <iostream>

namespace gloop {

	bool Physics::doCollide(const Rectangle& lhs, const Rectangle& rhs, Penetration& p){
        Vector2f normal = rhs.getCenter() - lhs.getCenter();
        Vector2f overlap = lhs.getDiagonal() / 2.0f + rhs.getDiagonal() / 2.0f - Vector2f::absolute(normal);
        
        //std::cout << (lhs.getDiagonal() / 2.0f).x << " " << (lhs.getDiagonal() / 2.0f).y << std::endl;
        //std::cout << (lhs.getDiagonal() / 2.0f).y << " " << (lhs.getDiagonal() / 2.0f).y << std::endl;
        //std::cout << overlap.x << " " << overlap.y << " " << (overlap.x <= epsilon) << " " <<  (overlap.y <= epsilon) << std::endl;

        if (overlap.x <= epsilon || overlap.y <= epsilon) {
            return false;
        }

        //std::cout << std::endl;

        if (overlap.x < overlap.y) {
            if (normal.x < 0) {
                p.normal = { -1.0f, 0.0f };
            }
            else {
                p.normal = { 1.0f, 0.0f };
            }

            p.depth = overlap.x;
        }
        else {
            if (normal.y < 0) {
                p.normal = { 0.0f, -1.0f };
            }
            else {
                p.normal = { 0.0f,  1.0f };
            }

            p.depth = overlap.y;
        }

		return p.depth > Skin;;
	}

	collisionData gloop::Physics::collide(const Collidable& mainObject, const Rectangle& otherObject){
        Penetration p{ Vector2f{0,0},0 };
        collisionData res;

        if (!doCollide(mainObject.getCollisionBox(), otherObject, p)) // No collision occurs
            return res;

        // Correction
        res.correction = p.normal * -std::max(p.depth - 0.1f, 0.0f) * correctionCoeff;

        // Collision resolution
        Vector2f relativeVelocity = -mainObject.getSpeed();
        const float velocityAlongNormal = relativeVelocity.dot(p.normal);
        if (velocityAlongNormal > 0) {
            return res;
        }
        res.collisionOccured = true;
        const float impulseScalar = (1 + restitution) * velocityAlongNormal;
        res.collision = p.normal * impulseScalar;

		return res;
	}

	collisionData Physics::collide(const Collidable& mainObject, const std::vector<Rectangle>& otherObjects){
        collisionData res;
        int nbCollide = 0;
		for (auto& other : otherObjects) {
			auto collision = collide(mainObject, other);
            if (collision.collisionOccured) {
                nbCollide++;
                res += collision;
            }
		}
        return (nbCollide > 0) ? collisionData{res.collision / nbCollide, res.correction / nbCollide, true} : res;
	}

}