#pragma once

#include "./ComponentPool.h"
#include "./Components.h"
#include "./EntityID.h"
#include "./IDManager.h"


/*
===============================================================================

	While this is called the ECS, it's more accurately described as a data holder.
	Just a collection of component pools, an id manager, and some logic for deleting entities.
	Logic is maintained by the scene, renderer, etc.

	TODO: Shared components / Singleton components

===============================================================================
*/
class ECS {
public:
	IDManager								idManager;
	ComponentPool<ShapeComponent>			shapes;
	ComponentPool<TransformComponent>		transforms;

											ECS();
	void									Init();
	void									DeleteEntity(EntityID id);
};