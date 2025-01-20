///////////////////////////////////////////////////////////////////////////////
// Filename: Game.cpp
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
#include "SceneManager.h"
#include "InputManager.h"
#include "NetworkManager.h"

#include "MainMenuScene.h"


//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init() {
	// Singleton creation via initial call to GetInstance
	SceneManager::GetInstance();
	InputManager::GetInstance();
	NetworkManager::GetInstance();

	// Set initial scene
	SceneManager::GetInstance().ChangeScene( std::make_unique<MainMenuScene>() );
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update( const float deltaTime ) {
	// Handle incoming
	InputManager::GetInstance().UpdateInputs();
	SceneManager::GetInstance().Update();
	// Send outgoing
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render() {
	SceneManager::GetInstance().Render();
}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown() {
	NetworkManager::GetInstance().Shutdown();
}