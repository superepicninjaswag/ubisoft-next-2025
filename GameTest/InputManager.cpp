#include "stdafx.h"
#include "InputManager.h"

InputManager::InputManager() {
	std::vector<int> keysToTrack = { 'W', 'A', 'S', 'D', VK_LBUTTON, VK_RBUTTON };
	
	for ( auto key : keysToTrack ) {
		trackedKeys.emplace(key, KeyState::Idle);
	}
}

void InputManager::updateInputs() {
	previousMousePosition = currentMousePosition;
	App::GetMousePos(currentMousePosition.x, currentMousePosition.y);

	for ( auto & keyAndState : trackedKeys ) {
		const int key = keyAndState.first;
		KeyState &state = keyAndState.second;
		const bool currentlyPressed = App::IsKeyPressed(key);

		switch ( state ) {
			case KeyState::Idle: {
				state = ( currentlyPressed ) ? KeyState::Pressed : KeyState::Idle;
				break;
			}
			case KeyState::Pressed: {
				state = ( currentlyPressed ) ? KeyState::Held : KeyState::Released;
				break;
			}
			case KeyState::Held: {
				state = ( currentlyPressed ) ? KeyState::Held : KeyState::Released;
				break;
			}
			case KeyState::Released: {
				state = ( currentlyPressed ) ? KeyState::Pressed : KeyState::Idle;
				break;
			}
		}
	}
}

KeyState InputManager::GetKeyState(const int key) {
	return trackedKeys[key];
}
