#pragma once

#include "InputManager.h"

class UIElement {
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
};