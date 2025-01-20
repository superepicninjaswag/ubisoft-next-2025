#include "stdafx.h"
#include "LobbyScene.h"
#include "NetworkManager.h"

LobbyScene::LobbyScene() {

}

void LobbyScene::Load() {

}

void LobbyScene::Unload() {
	ui.ShutDown();
}

void LobbyScene::Update() {
	NetworkManager::GetInstance().ReceivePackets();
	NetworkManager::GetInstance().UpdateLobbyClient();

	ui.Update();
}

void LobbyScene::Render() {
	ui.Draw();
}
