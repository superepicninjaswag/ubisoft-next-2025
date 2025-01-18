#pragma once


#include "./Vec2.h"

struct PhysicsBodyComponent {
	Vec2				velocity;
	Vec2				acceleration;
	Vec2				forceAccumulation;

	float				damping;
	float				inverseMass;

						PhysicsBodyComponent();

	void				SetMass( const float mass);
	void				AddForce( const Vec2 force );
};