#pragma once

#include "EntityID.h"
#include "Vec2.h"

class Collision {
public:
	EntityID		collidingBodies[2];
	float			restitution;
	Vec2			collisionNormal;
	float			penetration;

					Collision();
};