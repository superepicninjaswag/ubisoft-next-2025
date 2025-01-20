#include "stdafx.h"
#include "SceneManager.h"
#include "JoinSceneUI.h"
#include "MainMenuScene.h"

JoinSceneUI::JoinSceneUI() {
	// ip label
	texts.emplace_back();
	texts.back().text = "ip:          .         .         .";
	texts.back().position.x = 485.0f;
	texts.back().position.y = 507.0f;

	// ip input
	textInputs.emplace_back( 3, Vec2( 512.0f, 500.0f ) );
	textInputs.back().name = "ip1";

	textInputs.emplace_back( 3, Vec2( 562.0f, 500.0f ) );
	textInputs.back().name = "ip2";

	textInputs.emplace_back( 3, Vec2( 612.0f, 500.0f ) );
	textInputs.back().name = "ip3";

	textInputs.emplace_back( 3, Vec2( 662.0f, 500.0f ) );
	textInputs.back().name = "ip4";

	// port label
	texts.emplace_back();
	texts.back().text = "port: ";
	texts.back().position.x = 465.0f;
	texts.back().position.y = 407.0f;

	// port input
	textInputs.emplace_back( 6, Vec2( 512.0f, 400.0f ) );
	textInputs.back().name = "port";

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
				bool ip1 = GetInputByName( "ip1" )->IsNumeric();
				bool ip2 = GetInputByName( "ip2" )->IsNumeric();
				bool ip3 = GetInputByName( "ip3" )->IsNumeric();
				bool ip4 = GetInputByName( "ip4" )->IsNumeric();
				bool port = GetInputByName( "port" )->IsNumeric();
				if ( ip1 && ip2 && ip3 && ip4 && port) {
					SceneManager::GetInstance().ChangeScene(std::make_unique<MainMenuScene>());
				}
			}
		}
		uiEventQueue.clear();
	}
}