#pragma once


#include "./Vector2.h"

struct TransformComponent {
	Vector2 position;
	Vector2 rotation;

			TransformComponent();
			TransformComponent(float x, float y);
};