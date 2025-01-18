#include "stdafx.h"
#include "ECS.h"

ECS::ECS() {
	RegisterComponent<PhysicsBodyComponent>();
	RegisterComponent<ShapeComponent>();
	RegisterComponent<TransformComponent>();
}

void ECS::Init() {
	GetPool<PhysicsBodyComponent>()->Init(100);
	GetPool<ShapeComponent>()->Init( 100 );
	GetPool<TransformComponent>()->Init( 100 );
}

void ECS::DeleteEntity(EntityID id) {
	idManager.RecycleID(id);

	GetPool<PhysicsBodyComponent>()->Delete( id );
	GetPool<ShapeComponent>()->Delete( id );
	GetPool<TransformComponent>()->Delete( id );
}