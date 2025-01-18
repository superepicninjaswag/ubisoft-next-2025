#pragma once


#include "./Vec2.h"

struct PhysicsBodyComponent {
						PhysicsBodyComponent();

	void				Integrate( const float deltaTime, Vec2& position );
	void				SetMass( const float mass);
	void				SetGravity( const float gravity );
	void				SetDamping( const float damping );
	void				AddForce( const Vec2 force );
private:
	Vec2				velocity;
	Vec2				acceleration;
	Vec2				forceAccumulation;
	Vec2				gravity;

	float				damping;
	float				inverseMass;
};