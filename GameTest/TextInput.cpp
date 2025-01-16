#include "stdafx.h"
#include "TextInput.h"


TextInput::TextInput(int characterLimit) : text("abcdefghijklmnopqrstuvwxyz0123456789!.?;"), cursor("|"), cursorLocation(0), blinkingCursorTimer(0), characterLimit(characterLimit), focused(true) {
	position.x = 360;
	position.y = 360;

	int characterWidthToPixelRatio = 10;
	int characterHeightInPixels = 25;

	// Bottom left
	points[0].x = position.x;
	points[0].y = position.y;

	// Top left
	points[1].x = position.x;
	points[1].y = position.y + characterHeightInPixels;

	// Top right
	points[2].x = position.x + characterLimit * characterWidthToPixelRatio;
	points[2].y = position.y + characterHeightInPixels;

	// Bottom right
	points[3].x = position.x + characterLimit * characterWidthToPixelRatio;
	points[3].y = position.y;
}

void TextInput::draw() {
	for (int i = 0; i < 4; i++) {
		App::DrawLine(points[i].x, points[i].y, points[(i + 1) % 4].x, points[(i + 1) % 4].y);
	}

	std::string textWithCursor = text;
	if ( focused ) {
		if (blinkingCursorTimer < 30) {
			if (text.empty()) {
				textWithCursor.append(cursor);
			}
			else {
				textWithCursor.insert(cursorLocation, cursor);
			}
		}
	}

	App::Print(position.x, position.y + 6, textWithCursor.c_str());	// I add to the y position to align the text with the box better
}

void TextInput::update() {
	blinkingCursorTimer = (blinkingCursorTimer + 1) % 60;

	Vec2 mouse = InputManager::GetInstance().currentMousePosition;
	Vec2& topLeft = points[1];
	Vec2& bottomRight = points[3];
	bool withinBox = mouse.x >= topLeft.x && mouse.x <= bottomRight.x && mouse.y <= topLeft.y && mouse.y >= bottomRight.y;


	if ( withinBox && InputManager::GetInstance().GetKeyState(VK_LBUTTON) == KeyState::Pressed ) {
			focused = true;
	} else if ( !withinBox && InputManager::GetInstance().GetKeyState(VK_LBUTTON) != KeyState::Idle ) {
			focused = false;
	}
}
