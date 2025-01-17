#include "stdafx.h"
#include "MainMenuScene.h"

void MainMenuScene::load()  {
	ecs.Init();
}

void MainMenuScene::unload() {

}

void MainMenuScene::update() {
	ui.update();
}

void MainMenuScene::render() {
	shapeRenderer.RenderShapes();
	ui.draw();
}

MainMenuScene::MainMenuScene() : shapeRenderer(ecs) {

}
