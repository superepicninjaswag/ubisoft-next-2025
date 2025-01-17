#pragma once

#include <string>
#include "Vec2.h"
#include "UIElement.h"

class Text : public UIElement {
public:
	std::string			text;
	Vec2				position;

						Text();
	void				Draw() override;
	void				Update() override;
};