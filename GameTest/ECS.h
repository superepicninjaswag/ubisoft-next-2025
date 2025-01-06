#pragma once

#include "./ComponentPool.h"
#include "./Components.h"
#include "./EntityID.h"
#include "./IDManager.h"


class ECS {
public:
	IDManager								idManager;
	ComponentPool<ShapeComponent>			shapes;
	ComponentPool<TransformComponent>		transforms;

											ECS();
	void									Init();
	void									DeleteEntity(EntityID id);
	void									UpdateSystems();

	// Systems
	// ...
};