#include "stdafx.h"
#include "LobbySceneUI.h"
#include "NetworkManager.h"


LobbySceneUI::LobbySceneUI() {
	if ( NetworkManager::GetInstance().isHost ) {
		// ip
		texts.emplace_back();
		texts.back().name = "ip";
		texts.back().text = "Local ip + port is " + NetworkManager::GetInstance().bindedIP + ":" + std::to_string(NetworkManager::GetInstance().port);
		texts.back().position.x = 370.0f;
		texts.back().position.y = 607.0f;

		// tip
		texts.emplace_back();
		texts.back().text = "If you use port forwarding and such, you'll need your public ip instead";
		texts.back().position.x = 260.0f;
		texts.back().position.y = 557.0f;

		// player list
		texts.emplace_back();
		texts.back().name = "connected";
		texts.back().text = "Connected players: ";
		texts.back().position.x = 445.0f;
		texts.back().position.y = 507.0f;

		// Start button
		buttons.emplace_back();
		buttons.back().name = "start";
		buttons.back().position.x = 512.0f;
		buttons.back().position.y = 300.0f;
		buttons.back().text = "Start";
		buttons.back().textOffset.x = -17.0f;
	} else {
		// reassurance
		texts.emplace_back();
		texts.back().text = "Waiting for host to start...or you typed something in wrong";
		texts.back().position.x = 300.0f;
		texts.back().position.y = 400.0f;
	}
}

void LobbySceneUI::OnUpdate() {
	Text* connectedText = GetTextByName("connected");
	if ( connectedText ) {
		connectedText->text = "Number of players: " + std::to_string(NetworkManager::GetInstance().numConnectedPlayers);
	}
}
