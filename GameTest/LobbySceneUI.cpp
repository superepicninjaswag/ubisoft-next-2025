#include "stdafx.h"
#include "LobbySceneUI.h"
#include "NetworkManager.h"


LobbySceneUI::LobbySceneUI() {
	// TODO!!!! IF HOST OR CLIENT


	// ip
	texts.emplace_back();
	texts.back().name = "ip";
	texts.back().text = "";
	texts.back().position.x = 485.0f;
	texts.back().position.y = 607.0f;

	// tip
	texts.emplace_back();
	texts.back().text = "If you use port forwarding and such, you'll need your public ip instead";
	texts.back().position.x = 405.0f;
	texts.back().position.y = 557.0f;

	// player list
	texts.emplace_back();
	texts.back().name = "connected";
	texts.back().text = "Connected players: ";
	texts.back().position.x = 485.0f;
	texts.back().position.y = 507.0f;

	// Start button
	buttons.emplace_back();
	buttons.back().name = "start";
	buttons.back().position.x = 512.0f;
	buttons.back().position.y = 300.0f;
	buttons.back().text = "Start";
	buttons.back().textOffset.x = -17.0f;
}

void LobbySceneUI::OnUpdate() {
	if ( NetworkManager::GetInstance().isHost ) {
		Text* t = GetTextByName( "ip" );
		t->text = "Your local ip is " + NetworkManager::GetInstance().bindedIP + ":" + std::to_string( NetworkManager::GetInstance().port );

		std::string newConnectedText = "Connected players: ";
		for ( Player &p : NetworkManager::GetInstance().connectedPlayers ) {
			char playerIP[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, &p.address.sin_addr, playerIP, INET_ADDRSTRLEN);
			newConnectedText += std::string( playerIP ) + ":" + std::to_string( ntohs( p.address.sin_port ) ) + ", ";
		}

		Text* connectedText = GetTextByName( "connected" );
		connectedText->text = newConnectedText;
	} else {

	}
}
