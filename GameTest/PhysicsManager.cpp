#include "stdafx.h"

#include "PhysicsManager.h"

PhysicsManager::PhysicsManager(ECS &ecs) : ecs(ecs), timeStep( (1.0f / APP_MAX_FRAME_RATE) ) {

}

void PhysicsManager::DetectCollisions() {

}

void PhysicsManager::ResolveCollisions() {
	ComponentPool<PhysicsBodyComponent>& bodies = *ecs.GetPool<PhysicsBodyComponent>();
	ComponentPool<TransformComponent>& transforms = *ecs.GetPool<TransformComponent>();

	for ( auto &collision : collisions ) {
		EntityID entityA = collision.collidingBodies[0];
		EntityID entityB = collision.collidingBodies[1];

		// First we resolve the new velocity
		Vec2 relativeVelocity = bodies.Get( entityA )->velocity - bodies.Get( entityB )->velocity;
		float seperatingVelocity = relativeVelocity.DotProduct( collision.collisionNormal );

		// They are already moving apart (which can happen if another collision resolved and modified one or more of these bodies)
		if ( seperatingVelocity > 0 ) {
			continue;
		}

		// A new seperating velocity is needed to "reflect" the collision
		float newSeperatingVelocity = -seperatingVelocity * collision.restitution;
		float deltaVelocity = newSeperatingVelocity - seperatingVelocity;

		// Need this so "reflecting" impulse is proportional to mass of each body
		float totalInverseMass = bodies.Get(entityA)->inverseMass + bodies.Get(entityB)->inverseMass;

		// But if both have infinite mass (which my collision detector should ignore), we don't change either's velocity.
		if ( totalInverseMass <= 0 ) {
			continue;
		}

		float impulse = deltaVelocity / totalInverseMass;
		Vec2 impulsePerUnitOfInverseMass = collision.collisionNormal.Scale( impulse );

		bodies.Get(entityA)->velocity = bodies.Get( entityA )->velocity + ( impulsePerUnitOfInverseMass.Scale( bodies.Get( entityA )->inverseMass ) );
		bodies.Get(entityB)->velocity = bodies.Get( entityB )->velocity + ( impulsePerUnitOfInverseMass.Scale( -( bodies.Get( entityB )->inverseMass ) ) );

		// Now we resolve the interpenetration
	}
	collisions.clear();
}


/* 
* Comments are a little excessive for this function because it makes it easier for me to
* keep track of what's happening and why
*/
void PhysicsManager::Integrate() {
	ComponentPool<PhysicsBodyComponent>& bodies = *ecs.GetPool<PhysicsBodyComponent>();
	ComponentPool<TransformComponent>& transforms = *ecs.GetPool<TransformComponent>();

	for (int i = 0; i < bodies.dense.size(); i++) {
		EntityID id = bodies.mirror[ i ];

		if ( ecs.HasAllComponents<PhysicsBodyComponent, TransformComponent>( id ) ) {
			PhysicsBodyComponent& body = bodies.dense[i];
			TransformComponent& transform = *transforms.Get( id );

			if (body.inverseMass > 0.0f) {
				// Update position based on current velocity
				transform.position += body.velocity.Scale( timeStep );

				// Calculate new acceleration based on forces currently acting on body
				body.acceleration.Zero();
				body.acceleration += body.forceAccumulation.Scale( body.inverseMass );

				// Update velocity using new acceleration
				body.velocity += body.acceleration.Scale( timeStep );

				// Apply damping to simulate "drag"
				body.velocity = body.velocity.Scale( powf( body.damping, timeStep ) );

				// Any forces still acting on this body will be accumulated next update.
				body.forceAccumulation.Zero();
			}
		}
	}
}