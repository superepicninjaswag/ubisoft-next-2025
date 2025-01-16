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
	void						draw() override;
	void						update();

private:
	Vec2						points[4];
	int							cursorLocation;
	int							blinkingCursorTimer;
	int							characterLimit;
	bool						focused;
	std::vector<int>			acceptableCharacters;
};