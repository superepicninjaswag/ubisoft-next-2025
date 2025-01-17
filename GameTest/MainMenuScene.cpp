#include "stdafx.h"
#include "MainMenuScene.h"

void MainMenuScene::Load()  {

}

void MainMenuScene::Unload() {
	ui.ShutDown();
}

void MainMenuScene::Update() {
	ui.Update();
}

void MainMenuScene::Render() {
	ui.Draw();
}

MainMenuScene::MainMenuScene() {

}
