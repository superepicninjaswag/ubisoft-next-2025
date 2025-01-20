#pragma once

#include "ECS.h"
#include "Scene.h"
#include "LobbySceneUI.h"



class LobbyScene : public Scene {
public:
	ECS						ecs;
	LobbySceneUI			ui;

							LobbyScene();	// If you are starting as host

	void					Load() override;
	void					Unload() override;
	void					Update() override;
	void					Render() override;
};