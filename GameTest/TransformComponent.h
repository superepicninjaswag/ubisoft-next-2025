#pragma once


#include "./Vec2.h"

struct TransformComponent {
	Vec2 position;
	Vec2 rotation;

			TransformComponent();
			TransformComponent(float x, float y);
};