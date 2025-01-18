#include "stdafx.h"
#include "PhysicsBodyComponent.h"

PhysicsBodyComponent::PhysicsBodyComponent() : damping(0.0f), inverseMass(0.0f) {

}

void PhysicsBodyComponent::Integrate( const float deltaTime, Vec2& position) {
	// Infinite masses shouldn't move and
	// if deltaTime is somehow 0, then nothing
	// has changed since last time.
	if ( inverseMass > 0.0f )
	{
		position += velocity.Scale( deltaTime );

		acceleration.Zero();
		acceleration += forceAccumulation.Scale( inverseMass );

		velocity += acceleration.Scale( deltaTime );
		velocity = velocity.Scale( powf( damping, deltaTime ) );

		forceAccumulation.x = 0;
		forceAccumulation.y = 0;
	}
}

void PhysicsBodyComponent::SetMass( const float mass ){
	if (mass != 0.0f)
	{
		inverseMass = 1.0f / mass;
	}
}

void PhysicsBodyComponent::SetDamping( const float d ) {
	this->damping = d;
}

void PhysicsBodyComponent::AddForce( const Vec2 force ) {
	forceAccumulation += force;
}
