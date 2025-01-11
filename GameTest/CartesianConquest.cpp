///////////////////////////////////////////////////////////////////////////////
// Filename: GameTest.cpp
// Provides a demo of how to use the API
///////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
#include "app\app.h"
//------------------------------------------------------------------------
#include "ECS.h"
#include "InputManager.h"

#include "Text.h"
#include "Button.h"


/* TODO:
 * Shared components / Singleton components
 * Systems vector that is looped
 * Input buffer for rollback
 * UI system
 * Scene manager
 * Player input manager and event system
 */
ECS ecs;
InputManager inputManager;

Text test;
Button testb;
int frameNumber = 0;

std::vector<Text> garbage;

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init() {
	ecs.Init();
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update( const float deltaTime ) {
	inputManager.updateInputs();

	if ( inputManager.GetKeyState(VK_LBUTTON) == KeyState::Pressed ) {
		garbage.emplace_back();
		garbage.back().position = inputManager.currentMousePosition;
	}
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render() {
	ecs.DrawShapes();
	test.draw();
	testb.draw();
	for (auto &t : garbage) {
		t.draw();
	}
}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown() {

}