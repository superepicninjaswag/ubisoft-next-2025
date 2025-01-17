#include "stdafx.h"
#include "ECS.h"

ECS::ECS() {
	RegisterComponent<ShapeComponent>();
	RegisterComponent<TransformComponent>();
}

void ECS::Init() {
	GetPool<ShapeComponent>()->Init( 100 );
	GetPool<TransformComponent>()->Init( 100 );
}

void ECS::DeleteEntity(EntityID id) {
	idManager.RecycleID(id);

	GetPool<ShapeComponent>()->Delete( id );
	GetPool<TransformComponent>()->Delete( id );
}