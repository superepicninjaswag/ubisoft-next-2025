#include "stdafx.h"
#include "TextInput.h"


TextInput::TextInput(int characterLimit) : text(""), cursor("|"), cursorLocation(0), blinkingCursorTimer(0), characterLimit(characterLimit), focused(false) {
	acceptableCharacters = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
							'0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

	position.x = 360;
	position.y = 360;

	int characterWidthToPixelRatio = 13;
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
		App::DrawLine(points[ i ].x, points[ i ].y, points[ ( i + 1 ) % 4 ].x, points[ ( i + 1 ) % 4 ].y);
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

	if ( focused ) {
		/*
		* TODO: Add timer so that characters aren't deleted every update and the cursor doesn't move every update
		* It's a bit too fast otherwise. Some inital googling says 300ish ms before repeating deletes or move operations is comfortable for users
		*/ 

		// Move cursor
		KeyState leftArrowState = InputManager::GetInstance().GetKeyState( VK_LEFT );
		bool isLeftArrowActive = leftArrowState == KeyState::Pressed || leftArrowState == KeyState::Held;

		KeyState rightArrowState = InputManager::GetInstance().GetKeyState(VK_RIGHT);
		bool isRightArrowActive = rightArrowState == KeyState::Pressed || rightArrowState == KeyState::Held;

		int cursorDirection = 1 * isRightArrowActive + (-1 * isLeftArrowActive);
		cursorLocation += cursorDirection;

		// Don't blink if moving cursor
		if ( cursorDirection != 0 ) {
			blinkingCursorTimer = 0;
		}

		// Clamp cursor
		if ( cursorLocation < 0 ) {
			cursorLocation = 0;
		} else if ( cursorLocation > text.size() ) {
			cursorLocation = static_cast<int>(text.size());
		}


		// Backspace
		bool isBackspace = InputManager::GetInstance().GetKeyState(VK_BACK) == KeyState::Pressed || InputManager::GetInstance().GetKeyState(VK_BACK) == KeyState::Held;
		if (text.size() > 0 && cursorLocation > 0 && isBackspace ) {
			text.erase(cursorLocation - 1, 1);
			cursorLocation -= 1;
		}

		// Input characters
		for (auto character : acceptableCharacters) {
			if ( text.size() < characterLimit && InputManager::GetInstance().GetKeyState(character) == KeyState::Pressed ) {
				text.insert(cursorLocation, 1, static_cast<char>(character));
				cursorLocation++;
			}
		}
	}
}
