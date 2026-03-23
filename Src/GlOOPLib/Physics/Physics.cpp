#include "Physics.h"
#include <iostream>

namespace gloop {

	/*
	Vector2f normal = rhs.getCenter() - lhs.getCenter();
    Vector2f overlap = lhs.getSize() / 2 + rhs.getSize() / 2 - gf::abs(normal);

    if (overlap.x <= 0) {
      return false;
    }

    if (overlap.y <= 0) {
      return false;
    }

    if (overlap.x < overlap.y) {
      if (normal.x < 0) {
        p.normal = { -1.0f, 0.0f };
      } else {
        p.normal = {  1.0f, 0.0f };
      }

      p.depth = overlap.x;
    } else {
      if (normal.y < 0) {
        p.normal = { 0.0f, -1.0f };
      } else {
        p.normal = { 0.0f,  1.0f };
      }

      p.depth = overlap.y;
    }

    return p.depth > Skin;
	*/

	bool Physics::doCollide(const Rectangle& lhs, const Rectangle& rhs, Penetration& p){
        Vector2f normal = rhs.getCenter() - lhs.getCenter();
        Vector2f overlap = lhs.getSize() / 2 + rhs.getSize() / 2 - gf::abs(normal);

		return false;
	}

	collisionData gloop::Physics::collide(const Collidable& mainObject, const Rectangle& otherObject){
		Vector2f relativeVelocity = mainObject.getSpeed();

		return collisionData();
	}

	collisionData Physics::collide(const Collidable& mainObject, const std::vector<Rectangle>& otherObjects){
		for (auto& other : otherObjects) {
			collide(mainObject, other);
		}
		return collisionData();
	}

}