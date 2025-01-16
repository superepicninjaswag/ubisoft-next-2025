#include "stdafx.h"
#include "UI.h"

void UI::draw() {
	for ( auto& text : texts ) {
		text.draw();
	}

	for ( auto &button : buttons ) {
		button.draw();
	}

	for ( auto& textInput : textInputs ) {
		textInput.draw();
	}

	onUpdate();
}

void UI::update() {
	for (auto& text : texts) {
		//text.update();
	}

	for (auto& button : buttons) {
		//button.update();
	}

	for (auto& textInput : textInputs) {
		textInput.update();
	}
}
