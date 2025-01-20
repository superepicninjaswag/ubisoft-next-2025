#include "stdafx.h"
#include "GameLevelManager.h"

GameLevelManager::GameLevelManager() {
	playerCount = NetworkManager::GetInstance().numConnectedPlayers;
	
	for ( int i = 0; i < playerCount; i++ ) {
		shootDirections.emplace_back( 0.0f, 0.0f );
	}
}

void GameLevelManager::Update() {

}

void GameLevelManager::Draw() {

}
