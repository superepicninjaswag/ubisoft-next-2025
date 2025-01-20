#pragma once

#include "ECS.h"
#include "Scene.h"
#include "GameLevelUI.h"
#include "ShapeRenderer.h"
#include "PhysicsManager.h"
#include "Vec2.h"

#include <vector>


class GameLevelScene : public Scene {
public:
	// Scene related
	ECS						ecs;
	GameLeveleUI			ui;
	ShapeRenderer			sr;
	PhysicsManager			pm;

	// Game level related

	int						strokeCount = 0;	
	int						playerCount;
	std::vector<Vec2>		shootDirections;

							GameLevelScene( int level );

	void					Load() override;
	void					Unload() override;
	void					Update() override;
	void					Render() override;

	void					CreateBoundingBox();
	void					CreateGameOver();
	void					CreateLevelOne();
};