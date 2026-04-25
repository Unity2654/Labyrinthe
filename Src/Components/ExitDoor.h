#pragma once
#include "../GlOOPLib/Objects/Object3D.h"
#include "../GlOOPLib/Physics/Collidable.h"


class ExitDoor : public gloop::Object3D, public gloop::Collidable {

public:


	// Hérité via Collidable
	gloop::CollisionBox getCollisionBox() const override;

};