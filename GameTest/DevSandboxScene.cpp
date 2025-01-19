#include "stdafx.h"
#include "DevSandboxScene.h"
#include <vector>


std::vector<EntityID> circles;

DevSandboxScene::DevSandboxScene() : sr(ecs), pm(ecs) {

}

void DevSandboxScene::Load() {
	ecs.Init();

	// Test circle
	circles.push_back(ecs.idManager.GetNewId());

	ecs.GetPool<TransformComponent>()->Add(circles.back());
	ecs.GetPool<TransformComponent>()->Get(circles.back())->position.Set(500, 500);

	ecs.GetPool<ShapeComponent>()->Add(circles.back(), 20.0f);

	ecs.GetPool<PhysicsBodyComponent>()->Add(circles.back());
	ecs.GetPool<PhysicsBodyComponent>()->Get(circles.back())->damping = 0.9f;
	ecs.GetPool<PhysicsBodyComponent>()->Get(circles.back())->SetMass(20.0f);

	// Test circle
	circles.push_back(ecs.idManager.GetNewId());

	ecs.GetPool<TransformComponent>()->Add(circles.back());
	ecs.GetPool<TransformComponent>()->Get(circles.back())->position.Set(400, 500);

	ecs.GetPool<ShapeComponent>()->Add(circles.back(), 20.0f);

	ecs.GetPool<PhysicsBodyComponent>()->Add(circles.back());
	ecs.GetPool<PhysicsBodyComponent>()->Get(circles.back())->damping = 0.9f;
	ecs.GetPool<PhysicsBodyComponent>()->Get(circles.back())->SetMass(20.0f);

	// Test line 1
	EntityID temp2 = ecs.idManager.GetNewId();

	ecs.GetPool<TransformComponent>()->Add(temp2);
	ecs.GetPool<TransformComponent>()->Get(temp2)->position.Set(0, 0);

	ecs.GetPool<ShapeComponent>()->Add(temp2, Vec2( 100.0f, 100.0f ), Vec2( 700.0f, 100.0f ));

	ecs.GetPool<PhysicsBodyComponent>()->Add(temp2);
	ecs.GetPool<PhysicsBodyComponent>()->Get(temp2)->damping = 0.999f;

	// Test line 2
	EntityID temp3 = ecs.idManager.GetNewId();

	ecs.GetPool<TransformComponent>()->Add(temp3);
	ecs.GetPool<TransformComponent>()->Get(temp3)->position.Set(0, 0);

	ecs.GetPool<ShapeComponent>()->Add(temp3, Vec2(100.0f, 100.0f), Vec2(100.0f, 750.0f));

	ecs.GetPool<PhysicsBodyComponent>()->Add(temp3);
	ecs.GetPool<PhysicsBodyComponent>()->Get(temp3)->damping = 0.999f;

	// Test line 3
	EntityID temp4 = ecs.idManager.GetNewId();

	ecs.GetPool<TransformComponent>()->Add(temp4);
	ecs.GetPool<TransformComponent>()->Get(temp4)->position.Set(0, 0);

	ecs.GetPool<ShapeComponent>()->Add(temp4, Vec2(100.0f, 750.0f), Vec2(700.0f, 750.0f));

	ecs.GetPool<PhysicsBodyComponent>()->Add(temp4);
	ecs.GetPool<PhysicsBodyComponent>()->Get(temp4)->damping = 0.999f;

	// Test line 4
	EntityID temp5 = ecs.idManager.GetNewId();

	ecs.GetPool<TransformComponent>()->Add(temp5);
	ecs.GetPool<TransformComponent>()->Get(temp5)->position.Set(0, 0);

	ecs.GetPool<ShapeComponent>()->Add(temp5, Vec2(700.0f, 100.0f), Vec2(700.0f, 750.0f));

	ecs.GetPool<PhysicsBodyComponent>()->Add(temp5);
	ecs.GetPool<PhysicsBodyComponent>()->Get(temp5)->damping = 0.999f;
}

void DevSandboxScene::Unload() {
	ui.ShutDown();
}

void DevSandboxScene::Update() {
	for ( auto& id : circles ) {
		ecs.GetPool<PhysicsBodyComponent>()->Get(id)->AddForce(Vec2(0.0f, -9000.8f));
	}

	ui.Update();
	pm.Update();
}

void DevSandboxScene::Render() {
	ui.Draw();
	sr.RenderShapes();
}

