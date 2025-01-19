#include "stdafx.h"
#include "DevSandboxScene.h"

EntityID temp;
EntityID temp2;

DevSandboxScene::DevSandboxScene() : sr(ecs), pm(ecs) {

}

void DevSandboxScene::Load() {
	ecs.Init();

	// Test circle 1
	temp = ecs.idManager.GetNewId();

	ecs.GetPool<TransformComponent>()->Add(temp);
	ecs.GetPool<TransformComponent>()->Get(temp)->position.Set(500, 500);

    ecs.GetPool<ShapeComponent>()->Add(temp, 10.0f);

	ecs.GetPool<PhysicsBodyComponent>()->Add(temp);
	ecs.GetPool<PhysicsBodyComponent>()->Get(temp)->damping = 0.999f;
	ecs.GetPool<PhysicsBodyComponent>()->Get(temp)->SetMass( 20.0f );

	// Test circle 2
	temp2 = ecs.idManager.GetNewId();

	ecs.GetPool<TransformComponent>()->Add(temp2);
	ecs.GetPool<TransformComponent>()->Get(temp2)->position.Set(490, 250);

	ecs.GetPool<ShapeComponent>()->Add(temp2, 10.0f);

	ecs.GetPool<PhysicsBodyComponent>()->Add(temp2);
	ecs.GetPool<PhysicsBodyComponent>()->Get(temp2)->damping = 0.999f;
}

void DevSandboxScene::Unload() {
	ui.ShutDown();
}

void DevSandboxScene::Update() {
	ui.Update();
	ecs.GetPool<PhysicsBodyComponent>()->Get(temp)->AddForce( Vec2(0.0f, -9000.8f) );

	pm.Integrate();
	pm.DetectCollisions();
	pm.ResolveCollisions();
}

void DevSandboxScene::Render() {
	ui.Draw();
	sr.RenderShapes();
}

