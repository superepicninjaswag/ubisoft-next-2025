#pragma once

#include <string>
#include "Vec2.h"
#include "UIElement.h"

class Button : public UIElement {
public:
	std::string			text;
	Vec2				position;
	Vec2				size;
	Vec2				textOffset;

						Button();
	void				draw() override;
};