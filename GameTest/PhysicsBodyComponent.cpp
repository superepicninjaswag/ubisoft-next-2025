#include "stdafx.h"
#include "PhysicsBodyComponent.h"

PhysicsBodyComponent::PhysicsBodyComponent() : damping(1.0f), inverseMass(0.0f) {

}

void PhysicsBodyComponent::SetMass( const float mass ){
	if (mass != 0.0f)
	{
		inverseMass = 1.0f / mass;
	}
}

void PhysicsBodyComponent::AddForce( const Vec2 force ) {
	forceAccumulation += force;
}
