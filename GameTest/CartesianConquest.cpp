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


/* TODO:
 * Shared components / Singleton components
 * Systems vector that is looped
 * Input buffer for rollback
 * UI system
 * Scene manager
 * Player input manager and event system
 */
ECS ecs;

EntityID temp = ecs.idManager.GetNewId();

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init() {
	ecs.Init();
	ecs.shapes.Add(temp);
	ecs.shapes.Get(temp)->points.emplace_back(10.0f, 5.0f);
	ecs.shapes.Get(temp)->points.emplace_back(10.0f, -10.0f);
	ecs.shapes.Get(temp)->points.emplace_back(-5.0f, -10.0f);
	ecs.shapes.Get(temp)->points.emplace_back(-10.0f, 10.0f);
	ecs.transforms.Add(temp);
	ecs.transforms.Get(temp)->position.x = 501.0f;
	ecs.transforms.Get(temp)->position.y = 400.0f;
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update( const float deltaTime ) {
	
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render() {
	ecs.DrawShapes();
}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown() {

}