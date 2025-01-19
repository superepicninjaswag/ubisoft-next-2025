#pragma once


#include "./Vec2.h"

enum class Shape {
	CIRCLE,
	LINE
};

struct ShapeComponent {
	Shape						type;
	std::vector<Vec2>			points;

								ShapeComponent( const float radius );
								ShapeComponent( const Vec2 a, const Vec2 b );
};