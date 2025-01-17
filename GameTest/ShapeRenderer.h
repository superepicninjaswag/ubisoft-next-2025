#pragma once

#include "ECS.h"
#include "ComponentPool.h"
#include "Components.h"


/*
===============================================================================

	Responsible for drawing entities with a shape component

===============================================================================
*/
class ShapeRenderer {
public:
	ECS&										ecs;

												ShapeRenderer(ECS &ecs);

	void										RenderShapes();
};