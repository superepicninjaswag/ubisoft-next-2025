#pragma once

#include "ECS.h"
#include "Scene.h"
#include "ShapeRenderer.h"
#include "MainMenuUI.h"


class MainMenuScene : public Scene {
public:
	ECS						ecs;
	ShapeRenderer			shapeRenderer;
	MainMenuUI				ui;

	void					load();
	void					unload();
	void					update();
	void					render();

							MainMenuScene();
};