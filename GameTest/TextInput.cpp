#include "stdafx.h"
#include "TextInput.h"


TextInput::TextInput(int characterLimit) : text(""), cursor("|"), cursorLocation(0), blinkingCursorTimer(0), numUpdatesKeyHasBeenHeld(0), characterLimit(characterLimit), focused(false) {
	acceptableCharacters = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
							'0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	position.x = 360;
	position.y = 360;

	// Used when calculating box points too effectively contain text
	int characterWidthToPixelRatio = 13;
	int characterHeightInPixels = 25;

	// Box points
	points[0].x = position.x;
	points[0].y = position.y;

	points[1].x = position.x;
	points[1].y = position.y + characterHeightInPixels;

	points[2].x = position.x + characterLimit * characterWidthToPixelRatio;
	points[2].y = position.y + characterHeightInPixels;

	points[3].x = position.x + characterLimit * characterWidthToPixelRatio;
	points[3].y = position.y;
}

void TextInput::Draw() {
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

void TextInput::Update() {
	InputManager& im = InputManager::GetInstance();
	blinkingCursorTimer = (blinkingCursorTimer + 1) % 60;

	Vec2 mouse = im.currentMousePosition;
	Vec2& topLeft = points[1];
	Vec2& bottomRight = points[3];
	bool withinBox = mouse.x >= topLeft.x && mouse.x <= bottomRight.x && mouse.y <= topLeft.y && mouse.y >= bottomRight.y;

	if ( withinBox && im.GetKeyState(VK_LBUTTON) == KeyState::Pressed ) {
			focused = true;
	} else if ( !withinBox && im.GetKeyState(VK_LBUTTON) != KeyState::Idle ) {
			focused = false;
	}

	if ( focused ) {
		bool firstPressOrHeldLongEnough = ( numUpdatesKeyHasBeenHeld == 0 ) || ( numUpdatesKeyHasBeenHeld > updatesToWaitBeforeRepeat );

		// Move cursor
		KeyState leftArrowState = im.GetKeyState( VK_LEFT );
		bool isLeftArrowActive = ( leftArrowState == KeyState::Pressed ) || ( leftArrowState == KeyState::Held );

		KeyState rightArrowState = im.GetKeyState(VK_RIGHT);
		bool isRightArrowActive = ( rightArrowState == KeyState::Pressed ) || ( rightArrowState == KeyState::Held );

		int cursorDirection = 1 * isRightArrowActive + (-1 * isLeftArrowActive);
		if ( firstPressOrHeldLongEnough ) {
			cursorLocation += cursorDirection;
		}

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
		bool isBackspace = im.GetKeyState(VK_BACK) == KeyState::Pressed || im.GetKeyState(VK_BACK) == KeyState::Held;
		if (text.size() > 0 && cursorLocation > 0 && isBackspace && firstPressOrHeldLongEnough) {
			text.erase(cursorLocation - 1, 1);
			cursorLocation -= 1;
			blinkingCursorTimer = 0;
		}

		// Input character
		for (auto character : acceptableCharacters) {
			bool isKeyPressedOrHeld = im.GetKeyState(character) == KeyState::Pressed;
			if ( text.size() < characterLimit && isKeyPressedOrHeld ) {
				text.insert(cursorLocation, 1, static_cast<char>(character));
				cursorLocation++;
			}
		}

		// Counts if button been held long enough to repeat
		if ( isBackspace || isLeftArrowActive || isRightArrowActive ) {
			numUpdatesKeyHasBeenHeld += 1;
		} else {
			numUpdatesKeyHasBeenHeld = 0;
		}
	}
}
