#include "stdafx.h"
#include "DevSandboxScene.h"

EntityID temp;

void DevSandboxScene::Load() {
	ecs.Init();
	temp = ecs.idManager.GetNewId();

	ecs.GetPool<ShapeComponent>()->Add(temp);
	ecs.GetPool<TransformComponent>()->Add(temp);
}

void DevSandboxScene::Unload() {
	ui.ShutDown();
}

void DevSandboxScene::Update() {
	ui.Update();
}

void DevSandboxScene::Render() {
	ui.Draw();

	if ( ecs.HasAllComponents<ShapeComponent, TransformComponent>(temp) ) {
		App::DrawLine(0,0,500,500);
	}
}

DevSandboxScene::DevSandboxScene() {

}
