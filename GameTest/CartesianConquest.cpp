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
#include "ComponentPool.h"


ECS ecs;
EntityID tempID = ecs.idManager.GetNewId();
char textBuffer[64];

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
	ecs.DeleteEntity(tempID);
	tempID = ecs.idManager.GetNewId();
	ecs.transforms.Add(tempID);
	ecs.transforms.Get(tempID)->position.x = deltaTime;
	sprintf(textBuffer, "%u, %0.4f", tempID.GetVersion(), ecs.transforms.Get(tempID)->position.x);
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render() {	
	App::Print(50, 50, textBuffer, 1.0f, 0.0f, 1.0f, GLUT_BITMAP_HELVETICA_10);
}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown() {

}