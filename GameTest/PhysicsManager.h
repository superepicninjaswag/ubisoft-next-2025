#pragma once

#include "ECS.h"
#include <vector>
#include "Collision.h"


class PhysicsManager {
public:
	ECS&							ecs;
	std::vector<Collision>			collisions;

									PhysicsManager(ECS &ecs);

	void							Integrate(const float deltaTime);
};