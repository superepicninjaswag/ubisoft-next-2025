#include "stdafx.h"

#include "GameLevelScene.h"
#include "NetworkManager.h"


std::vector<EntityID> playerGolfBalls;
std::vector<Text> playerLabels;

Text playerNumIndicator;

GameLevelScene::GameLevelScene( int level ) : sr( ecs ), pm( ecs ) {
	currentLevel = level;
	NetworkManager::GetInstance().myLevel = currentLevel;
}

void GameLevelScene::Load() {
	ecs.Init();

	playerNumIndicator.position = Vec2( 780.0f, 700.0f );

	// Player details
	playerCount = NetworkManager::GetInstance().numConnectedPlayers;
	for (int i = 0; i < playerCount; i++) {
		shootDirections.emplace_back(0.0f, 0.0f);
	}

	// Create level
	if ( currentLevel == 1 ) {
		CreateBoundingBox();
		CreateLevelOne();
	} else {
		CreateGameOver();
	}

	// Network info
	NetworkManager::GetInstance().myLevel = currentLevel;
}

void GameLevelScene::Unload() {
	ui.ShutDown();
}

void GameLevelScene::Update() {
	NetworkManager::GetInstance().ReceivePackets();
	NetworkManager::GetInstance().UpdateGameLevelClient();
	NetworkManager::GetInstance().UpdateGameLevelServer();

	ui.Update();
	pm.Update();

	playerNumIndicator.text = "You are player " + std::to_string(NetworkManager::GetInstance().myPlayerNumber);
}

void GameLevelScene::Render() {
	sr.RenderShapes();
	ui.Draw();

	playerNumIndicator.Draw();	// Player # indicator

	for ( int i = 0; i < playerGolfBalls.size(); i++ ) {
		Vec2 pos = ecs.GetPool<TransformComponent>()->Get( playerGolfBalls[ i ])->position;
		playerLabels[ i ].position = pos;
		playerLabels[ i ].Draw();
	}
}

void GameLevelScene::DrawShootDirection() {
	int myPlayerNumber = 0;
}

void GameLevelScene::SpawnPlayer() {
	playerGolfBalls.push_back( ecs.idManager.GetNewId() );
	EntityID id = playerGolfBalls.back();
	playerLabels.emplace_back();
	playerLabels.back().text = std::to_string( playerGolfBalls.size() );

	ecs.GetPool<TransformComponent>()->Add( id );
	ecs.GetPool<TransformComponent>()->Get( id )->position.Set( 500, 500 );

	ecs.GetPool<ShapeComponent>()->Add( id, 20.0f );

	ecs.GetPool<PhysicsBodyComponent>()->Add( id );
	ecs.GetPool<PhysicsBodyComponent>()->Get( id )->damping = 0.3f;
	ecs.GetPool<PhysicsBodyComponent>()->Get( id )->SetMass( 20.0f );
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
	for ( int i = 0; i < NetworkManager::GetInstance().numConnectedPlayers; i++ ) {
		SpawnPlayer();
	}
}
