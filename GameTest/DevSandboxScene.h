#pragma once

#include "ECS.h"
#include "Scene.h"
#include "ShapeRenderer.h"
#include "DevSandboxUI.h"
#include "PhysicsManager.h"



class DevSandboxScene : public Scene {
public:
	ECS						ecs;
	DevSandboxUI			ui;
	ShapeRenderer			sr;
	PhysicsManager			pm;

							DevSandboxScene();

	void					Load() override;
	void					Unload() override;
	void					Update() override;
	void					Render() override;

};