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
	ecs.shapes.Get(temp)->points.emplace_back(10.0f, 10.0f);
	ecs.shapes.Get(temp)->points.emplace_back(10.0f, -10.0f);
	ecs.shapes.Get(temp)->points.emplace_back(-10.0f, -10.0f);
	ecs.shapes.Get(temp)->points.emplace_back(-10.0f, 10.0f);
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
	std::vector<ShapeComponent>& shapes = ecs.shapes.dense;
	for (int i = 0; i < shapes.size(); i++) {
		std::vector<Vec2>& points = shapes[i].points;
		int j = 0;
		for (; j < points.size() - 1; j++) {
			App::DrawLine(points[j].x, points[j].y, points[j + 1].x, points[j + 1].y);
		}
		App::DrawLine(points[j].x, points[j].y, points[0].x, points[0].y);
	}
}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown() {

}