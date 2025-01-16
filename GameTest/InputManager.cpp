#include "stdafx.h"
#include "InputManager.h"

InputManager::InputManager() {
	std::vector<int> keysToTrack = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
									'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
									VK_LBUTTON, VK_RBUTTON, VK_BACK, VK_RETURN,
									VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN };
	
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
