#include "stdafx.h"

#include "PhysicsManager.h"


/*
* Comments are a little excessive here because it makes it easier for me to
* keep track of what's happening and why
*/

PhysicsManager::PhysicsManager(ECS &ecs) : ecs(ecs), timeStep( (1.0f / APP_MAX_FRAME_RATE) ) {

}

void PhysicsManager::DetectCollisions() {
	ComponentPool<ShapeComponent>& colliders = *ecs.GetPool<ShapeComponent>();
	ComponentPool<TransformComponent>& transforms = *ecs.GetPool<TransformComponent>();

	// Naive check each collider pair for now
	for ( int i = 0; i < colliders.dense.size() - 1; i++ ) {
		EntityID entityA = colliders.mirror[i];

		if ( ecs.HasAllComponents<ShapeComponent, TransformComponent>( entityA ) ) {
			for ( int j = i + 1; j < colliders.dense.size(); j++ ) {
				EntityID entityB = colliders.mirror[j];

				if ( ecs.HasAllComponents<ShapeComponent, TransformComponent>( entityB ) ) {
					// Only handle circle circle collision for now
					if ( colliders.Get( entityA )->type == colliders.Get( entityB )->type && colliders.Get(entityA)->type == Shape::CIRCLE ) {
						Vec2 midLine = transforms.Get(entityA)->position - transforms.Get(entityB)->position;
						float radiusA = colliders.Get(entityA)->points[0].Length();
						float radiusB = colliders.Get(entityA)->points[0].Length();
						if ( midLine.Length() <= 0 || midLine.Length() >= radiusA + radiusB ) {
							continue;
						}


						collisions.emplace_back();
						collisions.back().restitution = 0.99f;
						collisions.back().penetration = radiusA + radiusB - midLine.Length();

						midLine.Normalize();
						collisions.back().collisionNormal = midLine;

						collisions.back().collidingBodies[0] = entityA;
						collisions.back().collidingBodies[1] = entityB;
					}
				}
			}
		}
	}
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
		if ( seperatingVelocity > 0.0f ) {
			continue;
		}

		// A new seperating velocity is needed to "reflect" the collision
		float newSeperatingVelocity = -seperatingVelocity * collision.restitution;
		float deltaVelocity = newSeperatingVelocity - seperatingVelocity;

		// Need this so "reflecting" impulse is proportional to mass of each body
		float totalInverseMass = bodies.Get(entityA)->inverseMass + bodies.Get(entityB)->inverseMass;

		// But if both have infinite mass (which my collision detector should ignore), we don't change either's velocity.
		if ( totalInverseMass <= 0.0f ) {
			continue;
		}

		float impulse = deltaVelocity / totalInverseMass;
		Vec2 impulsePerUnitOfInverseMass = collision.collisionNormal.Scale( impulse );

		bodies.Get( entityA )->SetVelocity( bodies.Get( entityA )->velocity + ( impulsePerUnitOfInverseMass.Scale( bodies.Get( entityA )->inverseMass ) ) );
		bodies.Get( entityB )->SetVelocity( bodies.Get( entityB )->velocity + ( impulsePerUnitOfInverseMass.Scale( bodies.Get( entityB )->inverseMass ) ) );

		// Next we resolve any interpenetration
		// First, are they even penetrating? There is a small chance they are just barely touching
		if ( collision.penetration <= 0.0f ) {
			continue;
		}

		// Objects displacement is proportional to mass (e.g. A boulder bouncing off a mountain)
		Vec2 displacementPerInverseMass = collision.collisionNormal.Scale( collision.penetration * totalInverseMass );
		transforms.Get( entityA )->position = transforms.Get( entityA )->position + displacementPerInverseMass.Scale( bodies.Get( entityA )->inverseMass );
		transforms.Get( entityB )->position = transforms.Get( entityB )->position + displacementPerInverseMass.Scale( bodies.Get( entityB )->inverseMass );
	}
	collisions.clear();
}

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