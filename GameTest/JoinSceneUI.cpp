#include "stdafx.h"
#include "SceneManager.h"
#include "JoinSceneUI.h"
#include "LobbyScene.h"
#include "NetworkManager.h"


JoinSceneUI::JoinSceneUI() {
	// ip label
	texts.emplace_back();
	texts.back().text = "ip:          .         .         .";
	texts.back().position.x = 485.0f;
	texts.back().position.y = 507.0f;

	// ip input
	textInputs.emplace_back( 3, Vec2( 512.0f, 500.0f ) );
	textInputs.back().name = "ip1";
	textInputs.back().text = "192";

	textInputs.emplace_back( 3, Vec2( 562.0f, 500.0f ) );
	textInputs.back().name = "ip2";
	textInputs.back().text = "168";

	textInputs.emplace_back( 3, Vec2( 612.0f, 500.0f ) );
	textInputs.back().name = "ip3";
	textInputs.back().text = "117";

	textInputs.emplace_back( 3, Vec2( 662.0f, 500.0f ) );
	textInputs.back().name = "ip4";
	textInputs.back().text = "1";

	// port label
	texts.emplace_back();
	texts.back().text = "port: ";
	texts.back().position.x = 465.0f;
	texts.back().position.y = 407.0f;

	// port input
	textInputs.emplace_back( 5, Vec2( 512.0f, 400.0f ) );
	textInputs.back().name = "port";
	textInputs.back().text = "60140";

	// Join button
	buttons.emplace_back();
	buttons.back().name = "join";
	buttons.back().position.x = 512.0f;
	buttons.back().position.y = 300.0f;
	buttons.back().text = "Join";
	buttons.back().textOffset.x = -17.0f;
}

void JoinSceneUI::OnUpdate() {
	if (!uiEventQueue.empty()) {
		for (auto& event : uiEventQueue) {
			if (event.uiElementName == "join" && event.eventType == EventType::Click) {
				TextInput* ip1 = GetInputByName("ip1");
				TextInput* ip2 = GetInputByName("ip2");
				TextInput* ip3 = GetInputByName("ip3");
				TextInput* ip4 = GetInputByName("ip4");
				TextInput* port = GetInputByName("port");

				bool ip1IsNum = ip1->IsNumeric();
				bool ip2IsNum = ip2->IsNumeric();
				bool ip3IsNum = ip3->IsNumeric();
				bool ip4IsNum = ip4->IsNumeric();
				bool portIsNum = port->IsNumeric();

				if ( ip1IsNum && ip2IsNum && ip3IsNum && ip4IsNum && portIsNum ) {
					std::string serverIP = ip1->text + "." + ip2->text + "." + ip3->text + "." + ip4->text;
					if ( NetworkManager::GetInstance().SetUpClient( serverIP, (u_short) std::stoi( port->text ) ) ) {
						SceneManager::GetInstance().ChangeScene( std::make_unique<LobbyScene>() );
					}
				}
			}
		}
		uiEventQueue.clear();
	}
}