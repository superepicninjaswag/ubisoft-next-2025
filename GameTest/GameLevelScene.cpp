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
	NetworkManager::GetInstance().ecs = &ecs;
	NetworkManager::GetInstance().playerGolfBalls = &playerGolfBalls;

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

	// Shoot
	if ( NetworkManager::GetInstance().isHost ) {
		Vec2 ballPos = ecs.GetPool<TransformComponent>()->Get(playerGolfBalls[0])->position;
		Vec2 target = InputManager::GetInstance().currentMousePosition;
		Vec2 forceDir = target - ballPos;
		forceDir.Normalize();
		if (InputManager::GetInstance().GetKeyState(VK_LBUTTON) == KeyState::Pressed) {
			ecs.GetPool<PhysicsBodyComponent>()->Get(playerGolfBalls[0])->AddForce(forceDir.Scale(2000000.f));
		}

		// Send updated position to clients
		for ( int i = 0; i < playerGolfBalls.size(); i++ ) {
			NetworkManager &nm = NetworkManager::GetInstance();
			ComponentPool<TransformComponent> &transforms = *ecs.GetPool<TransformComponent>();
			Vec2 pos = transforms.Get( playerGolfBalls[ i ] )->position;

			std::string data = std::to_string( pos.x ) + "," + std::to_string( pos.y ) + "," + std::to_string( i );
			std::vector<char> buffer( sizeof( PacketHeader ) + data.size() );
			buffer[0] = PacketHeader::POSITION;
			memcpy( buffer.data() + 1, data.c_str(), data.size() );
			for ( int j = 0; j < nm.connectedPlayers.size(); j++ ) {
				sendto(nm.mysocket, buffer.data(), (int)buffer.size(), 0, (sockaddr*)&nm.connectedPlayers[ j ].address, sizeof(nm.connectedPlayers[ j ].address));
			}
		}
	}
}

void GameLevelScene::Render() {
	sr.RenderShapes();
	ui.Draw();

	playerNumIndicator.Draw();	// Player # indicator

	for ( int i = 0; i < playerGolfBalls.size(); i++ ) {
		Vec2 pos = ecs.GetPool<TransformComponent>()->Get( playerGolfBalls[ i ] )->position;
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
