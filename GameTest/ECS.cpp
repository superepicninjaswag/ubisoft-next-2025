#include "stdafx.h"
#include "ECS.h"

ECS::ECS() {

}

void ECS::Init() {
	transforms.Init(300);
}

void ECS::DeleteEntity(EntityID id) {
	idManager.RecycleID(id);

	transforms.Delete(id);
}
