#pragma once

#include "Scene.h"

#include <memory>


/*
===============================================================================

	

===============================================================================
*/
class SceneManager {
public:
	std::unique_ptr<Scene>			currentScene;

	void							render();
	void							update();
	void							changeScene( std::unique_ptr<Scene> nextScene );

	static SceneManager&			GetInstance();

private:
									SceneManager();
};