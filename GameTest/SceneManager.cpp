#include "stdafx.h"

#include "SceneManager.h"


SceneManager::SceneManager() {

}

void SceneManager::update() {
	currentScene->update();
}

void SceneManager::render() {
	currentScene->render();
}

void SceneManager::changeScene( std::unique_ptr<Scene> nextScene ) {
	/*
	* There might be times where the current scene or next scene is null :(
	* For example, when the game executable first starts or if I'm working on
	* some funky debugging with manual scene transitions.
	*/
	if ( currentScene ) {
		currentScene.get()->unload();
	}

	currentScene = std::move( nextScene );

	if ( currentScene ) {
		currentScene.get()->load();
	}
}

SceneManager& SceneManager::GetInstance() {
	static SceneManager instance;
	return instance;
}
