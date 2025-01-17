#pragma once

#include <string>
#include "Vec2.h"
#include "UIElement.h"


/*
===============================================================================

	A UI "area" that accepts and displays text input. Displays as a single line.

===============================================================================
*/
class TextInput : public UIElement {
public:
	std::string					text;
	std::string					cursor;
	Vec2						position;

								TextInput(int characterLimit);
	void						Draw() override;
	void						Update() override;

private:
	std::vector<int>			acceptableCharacters;
	Vec2						points[4];
	int							characterLimit;
	bool						focused;

	int							cursorLocation;
	int							blinkingCursorTimer;

	int							numUpdatesKeyHasBeenHeld;
	const int					updatesToWaitBeforeRepeat = 20;
};