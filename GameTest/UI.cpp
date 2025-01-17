#include "stdafx.h"
#include "UI.h"

void UI::Draw() {
	for ( auto& text : texts ) {
		text.Draw();
	}

	for ( auto &button : buttons ) {
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
