#include "Physics.h"
#include <iostream>

namespace gloop {
	bool Physics::doCollide(const Rectangle& a, const Rectangle& b){
		auto aCorners = a.getCorners();
		auto bCorners = b.getCorners();

		if (aCorners[3].x < bCorners[0].x || aCorners[0].x > bCorners[3].x) return false;
		if (aCorners[3].y > bCorners[0].y || aCorners[0].y < bCorners[3].y) return false;
		
		return true;
	}

	collisionData gloop::Physics::collide(const Collidable& mainObject, const Rectangle& otherObject){
		std::cout << doCollide(mainObject.getCollisionBox(), otherObject) << std::endl;
		return collisionData();
	}

	collisionData Physics::collide(const Collidable& mainObject, const std::vector<Rectangle>& otherObjects){
		for (auto& other : otherObjects) {
			collide(mainObject, other);
		}
		return collisionData();
	}

}