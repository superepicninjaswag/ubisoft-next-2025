#include "stdafx.h"
#include "MainMenuUI.h"

MainMenuUI::MainMenuUI() {
	// Game title
	texts.emplace_back();
	texts.back().name = "title";
	texts.back().text = "Play It As It Lies";
	texts.back().position.x = 450.0f;
	texts.back().position.y = 512.0f;

	// Play button
	buttons.emplace_back();
	buttons.back().name = "play";
	buttons.back().position.x = 512.0f;
	buttons.back().position.y = 400.0f;
	buttons.back().text = "Play";
	buttons.back().textOffset.x = -16.0f;

	// Exit button
	buttons.emplace_back();
	buttons.back().name = "exit";
	buttons.back().position.x = 512.0f;
	buttons.back().position.y = 300.0f;
	buttons.back().text = "Exit";
	buttons.back().textOffset.x = -14.0f;
}

void MainMenuUI::OnUpdate() {
	if ( !uiEventQueue.empty() ) {
		for ( auto& event : uiEventQueue ) {
			if ( event.uiElementName == "exit" && event.eventType == EventType::Click) {
				glutLeaveMainLoop();
			}
		}
	}
}
