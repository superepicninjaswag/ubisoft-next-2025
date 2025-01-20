#pragma once

#include "Vec2.h"
#include "NetworkManager.h"
#include <vector>


class GameLevelManager {
public:
	int strokeCount = 0;
	int playerCount;
	std::vector<Vec2>		shootDirections;

							GameLevelManager();
	void					Update();
	void					Draw();
};