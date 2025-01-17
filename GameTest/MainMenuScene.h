#pragma once

#include "ECS.h"
#include "Scene.h"
#include "ShapeRenderer.h"
#include "MainMenuUI.h"


class MainMenuScene : public Scene {
public:
	MainMenuUI				ui;

	void					Load() override;
	void					Unload() override;
	void					Update() override;
	void					Render() override;

							MainMenuScene();
};