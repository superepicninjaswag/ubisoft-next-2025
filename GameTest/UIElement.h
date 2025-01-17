#pragma once

#include "InputManager.h"
#include <string>

class UIElement {
public:
	std::string name;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};