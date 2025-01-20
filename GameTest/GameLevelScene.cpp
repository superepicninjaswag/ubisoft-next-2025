#include "stdafx.h"

#include "GameLevelScene.h"
#include "NetworkManager.h"


GameLevelScene::GameLevelScene() {

}

void GameLevelScene::Load() {
	ui.ShutDown();
}

void GameLevelScene::Unload() {

}

void GameLevelScene::Update() {
	NetworkManager::GetInstance().ReceivePackets();
	NetworkManager::GetInstance().UpdateLobbyClient();
	NetworkManager::GetInstance().UpdateLobbyServer();

	ui.Update();
}

void GameLevelScene::Render() {
	ui.Draw();
}
