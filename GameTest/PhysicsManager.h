#pragma once

#include "ECS.h"
#include <vector>
#include "Collision.h"


class PhysicsManager {
public:
	ECS&							ecs;
	std::vector<Collision>			collisions;
	const float						timeStep;

									PhysicsManager(ECS &ecs);

	void							Integrate();
};