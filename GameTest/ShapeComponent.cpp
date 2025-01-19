#include "stdafx.h"

#include "ShapeComponent.h"


ShapeComponent::ShapeComponent( const float radius ) {
	type = Shape::CIRCLE;

    points = {
        Vec2(1.0f, 0.0f),              // Point at 0 degrees
        Vec2(0.9848f, 0.1736f),        // Point at 11.25 degrees
        Vec2(0.9239f, 0.3827f),        // Point at 22.5 degrees
        Vec2(0.8192f, 0.5736f),        // Point at 33.75 degrees
        Vec2(0.7071f, 0.7071f),        // Point at 45 degrees
        Vec2(0.5736f, 0.8192f),        // Point at 56.25 degrees
        Vec2(0.3827f, 0.9239f),        // Point at 67.5 degrees
        Vec2(0.1736f, 0.9848f),        // Point at 78.75 degrees
        Vec2(0.0f, 1.0f),              // Point at 90 degrees
        Vec2(-0.1736f, 0.9848f),       // Point at 101.25 degrees
        Vec2(-0.3827f, 0.9239f),       // Point at 112.5 degrees
        Vec2(-0.5736f, 0.8192f),       // Point at 123.75 degrees
        Vec2(-0.7071f, 0.7071f),       // Point at 135 degrees
        Vec2(-0.8192f, 0.5736f),       // Point at 146.25 degrees
        Vec2(-0.9239f, 0.3827f),       // Point at 157.5 degrees
        Vec2(-0.9848f, 0.1736f),       // Point at 168.75 degrees
        Vec2(-1.0f, 0.0f),             // Point at 180 degrees
        Vec2(-0.9848f, -0.1736f),      // Point at 191.25 degrees
        Vec2(-0.9239f, -0.3827f),      // Point at 202.5 degrees
        Vec2(-0.8192f, -0.5736f),      // Point at 213.75 degrees
        Vec2(-0.7071f, -0.7071f),      // Point at 225 degrees
        Vec2(-0.5736f, -0.8192f),      // Point at 236.25 degrees
        Vec2(-0.3827f, -0.9239f),      // Point at 247.5 degrees
        Vec2(-0.1736f, -0.9848f),      // Point at 258.75 degrees
        Vec2(0.0f, -1.0f),             // Point at 270 degrees
        Vec2(0.1736f, -0.9848f),       // Point at 281.25 degrees
        Vec2(0.3827f, -0.9239f),       // Point at 292.5 degrees
        Vec2(0.5736f, -0.8192f),       // Point at 303.75 degrees
        Vec2(0.7071f, -0.7071f),       // Point at 315 degrees
        Vec2(0.8192f, -0.5736f),       // Point at 326.25 degrees
        Vec2(0.9239f, -0.3827f),       // Point at 337.5 degrees
        Vec2(0.9848f, -0.1736f)        // Point at 348.75 degrees
    };

    for ( Vec2 &p : points ) {
        p = p.Scale( radius );
    }
}

ShapeComponent::ShapeComponent(const Vec2 a, const Vec2 b) {
    type = Shape::LINE;

    points.push_back(a);
    points.push_back(b);
}
