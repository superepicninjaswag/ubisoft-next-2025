#pragma once

#include <functional>
#include <string>
#include "Vec2.h"
#include "UIElement.h"
#include "UIEvent.h"

class Button : public UIElement {
public:
	std::string						text;
	Vec2							textOffset;

	bool							hovering;

	Vec2							points[4];
	Vec2							position;
	Vec2							size;

	float							r;
	float							g;
	float							b;

									Button();
	void							Draw() override;
	void							Update() override;
};