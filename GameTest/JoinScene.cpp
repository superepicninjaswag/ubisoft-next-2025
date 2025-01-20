#include "stdafx.h"
#include "JoinScene.h"

JoinScene::JoinScene() {

}

void JoinScene::Load() {

}

void JoinScene::Unload() {
	ui.ShutDown();
}

void JoinScene::Update() {
	ui.Update();
}

void JoinScene::Render() {
	ui.Draw();
}
