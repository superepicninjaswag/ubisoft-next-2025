#pragma once

#include "./ComponentPool.h"
#include "./Components.h"
#include "./EntityID.h"


class ECS {
public:
	ComponentPool<TransformComponent>	transforms;

										ECS();
	void								Init();
	void								DeleteEntity(EntityID id);
};