#include "stdafx.h"

#include "Text.h"

Text::Text() {
	text = "REPLACE ME";
	position.x = 451;
	position.y = 451;
}

void Text::draw() {
	App::Print(position.x, position.y, text.c_str());
}
