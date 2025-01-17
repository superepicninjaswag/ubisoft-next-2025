#include "stdafx.h"
#include "DevSandboxScene.h"

void DevSandboxScene::Load() {

}

void DevSandboxScene::Unload() {
	ui.ShutDown();
}

void DevSandboxScene::Update() {
	ui.Update();
}

void DevSandboxScene::Render() {
	ui.Draw();
}

DevSandboxScene::DevSandboxScene() {

}
