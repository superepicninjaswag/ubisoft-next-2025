#include "stdafx.h"

#include "GameLevelScene.h"
#include "NetworkManager.h"


std::vector<EntityID> circless;

GameLevelScene::GameLevelScene( int level ) : sr( ecs ), pm( ecs ) {
	if ( level == 0 ) {
		CreateGameOver();
	} else if ( level == 1 ) {
		CreateBoundingBox();
		CreateLevelOne();
	} else if ( level == 2 ) {

	} else if ( level == 3 ) {

	} else {

	}
}

void GameLevelScene::Load() {
	ecs.Init();
}

void GameLevelScene::Unload() {
	ui.ShutDown();
}

void GameLevelScene::Update() {
	NetworkManager::GetInstance().ReceivePackets();
	NetworkManager::GetInstance().UpdateLobbyClient();
	NetworkManager::GetInstance().UpdateLobbyServer();

	ui.Update();
	pm.Update();



	Vec2 ballPos = ecs.GetPool<TransformComponent>()->Get(circless[0])->position;
	Vec2 target = InputManager::GetInstance().currentMousePosition;
	Vec2 forceDir = target - ballPos;
	forceDir.Normalize();
	if (InputManager::GetInstance().GetKeyState(VK_LBUTTON) == KeyState::Pressed) {
		ecs.GetPool<PhysicsBodyComponent>()->Get(circless[0])->AddForce( forceDir.Scale( 2000000.f ) );
	}
}

void GameLevelScene::Render() {
	sr.RenderShapes();
	ui.Draw();
}

void GameLevelScene::CreateBoundingBox() {
	EntityID bottom = ecs.idManager.GetNewId();
	ecs.GetPool<TransformComponent>()->Add( bottom );
	ecs.GetPool<TransformComponent>()->Get( bottom )->position.Set(0, 0);
	ecs.GetPool<ShapeComponent>()->Add( bottom , Vec2( 100.0f, 100.0f ), Vec2( 924.0f, 100.0f ) );
	ecs.GetPool<PhysicsBodyComponent>()->Add( bottom );
	ecs.GetPool<PhysicsBodyComponent>()->Get( bottom )->damping = 1.0f;

	EntityID top = ecs.idManager.GetNewId();
	ecs.GetPool<TransformComponent>()->Add( top );
	ecs.GetPool<TransformComponent>()->Get( top )->position.Set(0, 0);
	ecs.GetPool<ShapeComponent>()->Add( top , Vec2( 100.0f, 668.0f ), Vec2( 924.0f, 668.0f ) );
	ecs.GetPool<PhysicsBodyComponent>()->Add( top );
	ecs.GetPool<PhysicsBodyComponent>()->Get( top )->damping = 1.0f;

	EntityID right = ecs.idManager.GetNewId();
	ecs.GetPool<TransformComponent>()->Add( right );
	ecs.GetPool<TransformComponent>()->Get( right )->position.Set(0, 0);
	ecs.GetPool<ShapeComponent>()->Add( right , Vec2( 924.0f, 100.0f ), Vec2( 924.0f, 668.0f ) );
	ecs.GetPool<PhysicsBodyComponent>()->Add( right );
	ecs.GetPool<PhysicsBodyComponent>()->Get( right )->damping = 1.0f;

	EntityID left = ecs.idManager.GetNewId();
	ecs.GetPool<TransformComponent>()->Add( left );
	ecs.GetPool<TransformComponent>()->Get( left )->position.Set(0, 0);
	ecs.GetPool<ShapeComponent>()->Add( left , Vec2( 100.0f, 100.0f ), Vec2( 100.0f, 668.0f ) );
	ecs.GetPool<PhysicsBodyComponent>()->Add( left );
	ecs.GetPool<PhysicsBodyComponent>()->Get( left )->damping = 1.0f;
}

void GameLevelScene::CreateGameOver() {
	// Game over label
	// Rank
	// Exit button
}

void GameLevelScene::CreateLevelOne() {
	// Test circle
	circless.push_back(ecs.idManager.GetNewId());

	ecs.GetPool<TransformComponent>()->Add(circless.back());
	ecs.GetPool<TransformComponent>()->Get(circless.back())->position.Set(500, 500);

	ecs.GetPool<ShapeComponent>()->Add(circless.back(), 20.0f);

	ecs.GetPool<PhysicsBodyComponent>()->Add(circless.back());
	ecs.GetPool<PhysicsBodyComponent>()->Get(circless.back())->damping = 0.3f;
	ecs.GetPool<PhysicsBodyComponent>()->Get(circless.back())->SetMass(20.0f);

	// Test circle
	circless.push_back(ecs.idManager.GetNewId());

	ecs.GetPool<TransformComponent>()->Add(circless.back());
	ecs.GetPool<TransformComponent>()->Get(circless.back())->position.Set(500, 500);

	ecs.GetPool<ShapeComponent>()->Add(circless.back(), 20.0f);

	ecs.GetPool<PhysicsBodyComponent>()->Add(circless.back());
	ecs.GetPool<PhysicsBodyComponent>()->Get(circless.back())->damping = 0.3f;
	ecs.GetPool<PhysicsBodyComponent>()->Get(circless.back())->SetMass(20.0f);
}
