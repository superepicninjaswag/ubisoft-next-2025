#pragma once

#include "ECS.h"
#include "Scene.h"
#include "JoinSceneUI.h"



class JoinScene : public Scene {
public:
	ECS						ecs;
	JoinSceneUI				ui;

							JoinScene();

	void					Load() override;
	void					Unload() override;
	void					Update() override;
	void					Render() override;
};