#pragma once

#include "ECS.h"
#include "Scene.h"
#include "GameLevelUI.h"
#include "ShapeRenderer.h"
#include "PhysicsManager.h"
#include "GameLevelManager.h"
#include "Vec2.h"

#include <vector>


class GameLevelScene : public Scene {
public:
	ECS						ecs;
	GameLeveleUI			ui;
	ShapeRenderer			sr;
	PhysicsManager			pm;
	GameLevelManager		glm;

							GameLevelScene( int level );

	void					Load() override;
	void					Unload() override;
	void					Update() override;
	void					Render() override;

	void					CreateBoundingBox();
	void					CreateGameOver();
	void					CreateLevelOne();
};