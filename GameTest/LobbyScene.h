#pragma once

#include "ECS.h"
#include "Scene.h"



class LobbyScene : public Scene {
public:
	ECS						ecs;

							LobbyScene();

	void					Load() override;
	void					Unload() override;
	void					Update() override;
	void					Render() override;
};