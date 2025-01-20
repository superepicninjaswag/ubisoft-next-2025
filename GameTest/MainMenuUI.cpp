#include "stdafx.h"
#include "MainMenuUI.h"
#include "SceneManager.h"
#include "LobbyScene.h"
#include "JoinScene.h"


MainMenuUI::MainMenuUI() {
	// Game title
	texts.emplace_back();
	texts.back().name = "title";
	texts.back().text = "Play It As It Lies";
	texts.back().position.x = 450.0f;
	texts.back().position.y = 512.0f;

	// Host button
	buttons.emplace_back();
	buttons.back().name = "host";
	buttons.back().position.x = 512.0f;
	buttons.back().position.y = 400.0f;
	buttons.back().text = "Host";
	buttons.back().textOffset.x = -18.0f;

	// Join button
	buttons.emplace_back();
	buttons.back().name = "join";
	buttons.back().position.x = 512.0f;
	buttons.back().position.y = 300.0f;
	buttons.back().text = "Join";
	buttons.back().textOffset.x = -17.0f;

	// Exit button
	buttons.emplace_back();
	buttons.back().name = "exit";
	buttons.back().position.x = 512.0f;
	buttons.back().position.y = 200.0f;
	buttons.back().text = "Exit";
	buttons.back().textOffset.x = -14.0f;
}

void MainMenuUI::OnUpdate() {
	if ( !uiEventQueue.empty() ) {
		for ( auto& event : uiEventQueue ) {
			if (        event.uiElementName == "host" && event.eventType == EventType::Click ) {
				SceneManager::GetInstance().ChangeScene( std::make_unique<LobbyScene>() );
			} else if ( event.uiElementName == "join" && event.eventType == EventType::Click) {
				SceneManager::GetInstance().ChangeScene( std::make_unique<JoinScene>() );
			} else if ( event.uiElementName == "exit" && event.eventType == EventType::Click ) {
				glutLeaveMainLoop();
			}
		}
		uiEventQueue.clear();
	}
}
