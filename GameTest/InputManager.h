#pragma once

#include "Vec2.h"
#include "App/app.h"

#include <unordered_map>


enum class KeyState {
	Idle,
	Pressed,
	Held,
	Released
};

/*
===============================================================================

	Tracks the state of specified keys and mouse movement.

	TODO: tracked keys are listed in the constructor but as the game grows,
	it would be better to read which keys to track from a config file and
	generate/respond to events instead of directly looking for a key's state
	in the game systems.

===============================================================================
*/
class InputManager {
public:
	Vec2										currentMousePosition;
	Vec2										previousMousePosition;

	void										updateInputs();
	KeyState									GetKeyState(const int key);

	static InputManager&						GetInstance();

private:
												InputManager();
	std::unordered_map<int, KeyState>			trackedKeys;
};