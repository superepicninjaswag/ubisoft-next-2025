#include "stdafx.h"
#include "UI.h"

std::vector<UIEvent> UI::uiEventQueue;

void UI::Draw() {
	for ( auto& text : texts ) {
		text.Draw();
	}

	for ( auto& button : buttons ) {
		button.Draw();
	}

	for ( auto& textInput : textInputs ) {
		textInput.Draw();
	}

	OnUpdate();
}

void UI::Update() {
	for (auto& text : texts) {
		text.Update();
	}

	for (auto& button : buttons) {
		button.Update();
	}

	for (auto& textInput : textInputs) {
		textInput.Update();
	}
}

void UI::ShutDown() {
	uiEventQueue.clear();
}

Text* UI::GetTextByName(std::string name) {
	for ( auto& text : texts ) {
		if ( text.name == name ) {
			return &text;
		}
	}
	return nullptr;
}

TextInput* UI::GetInputByName( std::string name ) {
	for ( auto& textInput : textInputs ) {
		if ( textInput.name == name ) {
			return &textInput;
		}
	}
	return nullptr;
}
