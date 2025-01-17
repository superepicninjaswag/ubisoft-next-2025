#include "stdafx.h"

#include "SceneManager.h"


SceneManager::SceneManager() {

}

void SceneManager::Update() {
	if ( currentScene ) {
		currentScene->Update();
	}
}

void SceneManager::Render() {
	if ( currentScene ) {
		currentScene->Render();
	}
}

void SceneManager::ChangeScene( std::unique_ptr<Scene> nextScene ) {
	/*
	* There might be times where the current scene or next scene is null :(
	* For example, when the game executable first starts or if I'm working on
	* some funky debugging with manual scene transitions.
	*/
	if ( currentScene ) {
		currentScene.get()->Unload();
	}

	currentScene = std::move( nextScene );

	if ( currentScene ) {
		currentScene.get()->Load();
	}
}

SceneManager& SceneManager::GetInstance() {
	static SceneManager instance;
	return instance;
}
