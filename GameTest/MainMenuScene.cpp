#include "stdafx.h"
#include "MainMenuScene.h"

void MainMenuScene::Load()  {
	ecs.Init();
}

void MainMenuScene::Unload() {

}

void MainMenuScene::Update() {
	ui.Update();
}

void MainMenuScene::Render() {
	shapeRenderer.RenderShapes();
	ui.Draw();
}

MainMenuScene::MainMenuScene() : shapeRenderer(ecs) {

}
