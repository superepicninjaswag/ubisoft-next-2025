#pragma once

#include "ECS.h"
#include "Scene.h"
#include "ShapeRenderer.h"
#include "DevSandboxUI.h"



class DevSandboxScene : public Scene {
public:
	ECS						ecs;
	DevSandboxUI			ui;

	void					Load() override;
	void					Unload() override;
	void					Update() override;
	void					Render() override;

							DevSandboxScene();
};