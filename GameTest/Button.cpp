#include "stdafx.h"
#include "Button.h"

Button::Button() {
	text = "CHANGE ME";
	position.x = 420;
	position.y = 420;
	size.x = 100;
	size.y = 50;
	textOffset.x = -50;
	textOffset.y = -5;
}

void Button::draw() {
	Vec2 points[4];

	points[0].x = position.x + size.x;
	points[0].y = position.y + size.y;

	points[1].x = position.x + size.x;
	points[1].y = position.y - size.y;

	points[2].x = position.x - size.x;
	points[2].y = position.y - size.y;

	points[3].x = position.x - size.x;
	points[3].y = position.y + size.y;

	for (int i = 0; i < 4; i++) {
		App::DrawLine(points[i].x, points[i].y, points[( i + 1 ) % 4].x, points[(i + 1) % 4].y);
	}

	App::Print(position.x + textOffset.x, position.y + textOffset.y, text.c_str());
}
