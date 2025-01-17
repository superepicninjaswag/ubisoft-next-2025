#include "stdafx.h"
#include "Button.h"
#include "UI.h"

Button::Button() {
	name = "";
	text = "CHANGE ME";
	position.x = 420;
	position.y = 420;
	size.x = 100;
	size.y = 30;
	textOffset.x = -50;
	textOffset.y = -6;

	hovering = false;

	r = 1.0f;
	g = 1.0f;
	b = 1.0f;
}

void Button::Draw() {
	points[0].x = position.x + size.x;
	points[0].y = position.y + size.y;

	points[1].x = position.x + size.x;
	points[1].y = position.y - size.y;

	points[2].x = position.x - size.x;
	points[2].y = position.y - size.y;

	points[3].x = position.x - size.x;
	points[3].y = position.y + size.y;

	for (int i = 0; i < 4; i++) {
		App::DrawLine(points[i].x, points[i].y, points[(i + 1) % 4].x, points[(i + 1) % 4].y, r, g, b);
	}

	App::Print(position.x + textOffset.x, position.y + textOffset.y, text.c_str(), r, g, b);
}

void Button::Update() {
	InputManager& im = InputManager::GetInstance();

	Vec2 mouse = im.currentMousePosition;
	Vec2& topLeft = points[3];
	Vec2& bottomRight = points[1];
	hovering = mouse.x >= topLeft.x && mouse.x <= bottomRight.x && mouse.y <= topLeft.y && mouse.y >= bottomRight.y;

	if ( hovering ) {
		r = 1.0f;
		g = 0.0f;
		b = 0.0f;
	} else {
		r = 1.0f;
		g = 1.0f;
		b = 1.0f;
	}

	// Generate click event
	if ( hovering && im.GetKeyState( VK_LBUTTON ) == KeyState::Pressed ) {
		UI::uiEventQueue.emplace_back(name, EventType::Click);
	}
}
