#pragma once

#include "ECS.h"
#include "Scene.h"
#include "GameLevelUI.h"



class GameLevelScene : public Scene {
public:
	ECS						ecs;
	GameLeveleUI			ui;

							GameLevelScene();

	void					Load() override;
	void					Unload() override;
	void					Update() override;
	void					Render() override;
};