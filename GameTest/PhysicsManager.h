#pragma once

#include "ECS.h"


class PhysicsManager {
public:
	ECS&			ecs;

					PhysicsManager(ECS &ecs);

	void			Integrate(const float deltaTime);
};