#include "Physics.h"

namespace gloop {
	collisionData gloop::Physics::collide(const Collidable& mainObject, const Collidable& otherObject)
	{
		return collisionData();
	}

	collisionData Physics::collide(const Collidable& mainObject, const std::vector<Collidable>& otherObjects)
	{
		return collisionData();
	}

}