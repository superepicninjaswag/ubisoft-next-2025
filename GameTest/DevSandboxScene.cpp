#include "stdafx.h"
#include "DevSandboxScene.h"

EntityID temp;


DevSandboxScene::DevSandboxScene() : sr(ecs), pm(ecs) {

}

void DevSandboxScene::Load() {
	ecs.Init();
	temp = ecs.idManager.GetNewId();

	ecs.GetPool<ShapeComponent>()->Add(temp);
	ShapeComponent* shape = ecs.GetPool<ShapeComponent>()->Get(temp);
	shape->points = {
		Vec2(50, 0),               // Point at 0 degrees
		Vec2(35.36f, 35.36f),      // Point at 45 degrees
		Vec2(0, 50),               // Point at 90 degrees
		Vec2(-35.36f, 35.36f),     // Point at 135 degrees
		Vec2(-50, 0),              // Point at 180 degrees
		Vec2(-35.36f, -35.36f),    // Point at 225 degrees
		Vec2(0, -50),              // Point at 270 degrees
		Vec2(35.36f, -35.36f)      // Point at 315 degrees
	};

	ecs.GetPool<TransformComponent>()->Add(temp);
	ecs.GetPool<TransformComponent>()->Get(temp)->position.Set( 500, 500 );

	ecs.GetPool<PhysicsBodyComponent>()->Add(temp);
	ecs.GetPool<PhysicsBodyComponent>()->Get(temp)->SetDamping( 0.98f );
	ecs.GetPool<PhysicsBodyComponent>()->Get(temp)->SetMass( 1000.0f );
}

void DevSandboxScene::Unload() {
	ui.ShutDown();
}

void DevSandboxScene::Update() {
	ui.Update();

	ecs.GetPool<PhysicsBodyComponent>()->Get(temp)->Integrate(((1.0f / APP_MAX_FRAME_RATE)), ecs.GetPool<TransformComponent>()->Get(temp)->position);
}

void DevSandboxScene::Render() {
	ui.Draw();
	sr.RenderShapes();

	if ( ecs.HasAllComponents<ShapeComponent, TransformComponent, PhysicsBodyComponent>(temp) ) {
		App::DrawLine(0,0,500,500);
	}
}

