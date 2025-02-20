#include "stdafx.h"

#include "PhysicsManager.h"
#include "NetworkManager.h"

/*
* Comments are a little excessive here because it makes it easier for me to
* keep track of what's happening and why
*/

PhysicsManager::PhysicsManager( ECS &ecs ) : ecs( ecs ), timeStep( (1.0f / APP_MAX_FRAME_RATE) ) {

}

void PhysicsManager::Update() {
	DetectCollisions();
	ResolveCollisions();
	Integrate();
}

void PhysicsManager::DetectCollisions() {
	ComponentPool<ShapeComponent>& colliders = *ecs.GetPool<ShapeComponent>();
	ComponentPool<TransformComponent>& transforms = *ecs.GetPool<TransformComponent>();
	// Player ball poll

	// Broad Phase: Only check what each player's golf ball is colliding with. Hazards, walls, etc are all static so no need to check them
	// TODO: Spatial Grid to speed up which walls and hazards to compare golf balls with
	for ( int i = 0; i < colliders.dense.size() - 1; i++ ) {

		// Narrow Phase
		EntityID entityA = colliders.mirror[i];
		if ( ecs.HasAllComponents<ShapeComponent, TransformComponent>( entityA ) ) {
			for ( int j = i + 1; j < colliders.dense.size(); j++ ) {
				EntityID entityB = colliders.mirror[j];

				if ( ecs.HasAllComponents<ShapeComponent, TransformComponent>( entityB ) ) {
					Shape colliderTypeA = colliders.Get( entityA )->type;
					Shape colliderTypeB = colliders.Get( entityB )->type;


					if ( colliderTypeA == Shape::CIRCLE && colliderTypeB == Shape::CIRCLE ) {
						Vec2 midLine = transforms.Get(entityA)->position - transforms.Get(entityB)->position;
						float radiusA = colliders.Get(entityA)->points[0].Length();
						float radiusB = colliders.Get(entityA)->points[0].Length();

						if ( midLine.Length() <= 0 || midLine.Length() >= radiusA + radiusB ) {
							continue;
						}

						collisions.emplace_back();
						collisions.back().restitution = 0.7f;
						collisions.back().penetration = radiusA + radiusB - midLine.Length();

						midLine.Normalize();
						collisions.back().collisionNormal = midLine;

						collisions.back().collidingBodies[0] = entityA;
						collisions.back().collidingBodies[1] = entityB;

					} else if ( colliderTypeA == Shape::CIRCLE && colliderTypeB == Shape::LINE || 
								colliderTypeA == Shape::LINE   && colliderTypeB == Shape::CIRCLE )
					{
						// Just for making the following code nicer
						EntityID circleID = entityA;
						EntityID lineID = entityB;
						if ( colliderTypeB == Shape::CIRCLE ) {
							std::swap( circleID, lineID );
						}

						// First find the closest point from the line generated by the line segment to the circle center
						Vec2 p1 = colliders.Get( lineID )->points[0];
						Vec2 p2 = colliders.Get( lineID )->points[1];
						Vec2 p3 = transforms.Get( circleID )->position;
						float u = ( ( p3.x - p1.x ) * ( p2.x - p1.x ) + ( p3.y - p1.y ) * ( p2.y - p1.y ) )
									/ 
								  ( ( p2 - p1 ).Length() * ( p2 - p1 ).Length() );

						Vec2 closestPoint;
						if ( u <= 0.0f ) {
							closestPoint = p1;
						} else if ( u >= 1.0f ) {
							closestPoint = p2;
						} else {
							closestPoint = p1 + ( p2 - p1 ).Scale( u );
						}
						
						float radius = colliders.Get( circleID )->points[0].Length();
						float radiusSquared = radius * radius;

						float distanceToPointSquared = ( p3 - closestPoint ).Length() * ( p3 - closestPoint ).Length();

						if ( distanceToPointSquared > radiusSquared ) {
							// No collision
						} else {
							collisions.emplace_back();
							collisions.back().restitution = 0.8f;

							Vec2 normal = p3 - closestPoint;
							collisions.back().penetration = radius - normal.Length();

							normal.Normalize();
							collisions.back().collisionNormal = normal;

							collisions.back().collidingBodies[0] = circleID;
							collisions.back().collidingBodies[1] = lineID;
						}
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

		if ( ecs.HasAllComponents<PhysicsBodyComponent, TransformComponent>( entityA ) && ecs.HasAllComponents<PhysicsBodyComponent, TransformComponent>( entityB ) ) {
			// First we resolve the new velocity
			Vec2 relativeVelocity = bodies.Get(entityA)->velocity - bodies.Get(entityB)->velocity;
			float seperatingVelocity = relativeVelocity.DotProduct(collision.collisionNormal);

			// They are already moving apart (which can happen if another collision resolved and modified one or more of these bodies)
			if (seperatingVelocity > 0.0f) {
				continue;
			}

			// A new seperating velocity is needed to "reflect" the collision
			float newSeperatingVelocity = -seperatingVelocity * collision.restitution;
			float deltaVelocity = newSeperatingVelocity - seperatingVelocity;

			// Need this so "reflecting" impulse is proportional to mass of each body
			float totalInverseMass = bodies.Get(entityA)->inverseMass + bodies.Get(entityB)->inverseMass;

			// But if both have infinite mass (which my collision detector should ignore), we don't change either's velocity.
			if (totalInverseMass <= 0.0f) {
				continue;
			}

			float impulse = deltaVelocity / totalInverseMass;
			Vec2 impulsePerUnitOfInverseMass = collision.collisionNormal.Scale(impulse);

			bodies.Get(entityA)->SetVelocity(bodies.Get(entityA)->velocity + (impulsePerUnitOfInverseMass.Scale(bodies.Get(entityA)->inverseMass)));
			bodies.Get(entityB)->SetVelocity(bodies.Get(entityB)->velocity - (impulsePerUnitOfInverseMass.Scale(bodies.Get(entityB)->inverseMass)));

			// Next we resolve any interpenetration
			// First, are they even penetrating? There is a small chance they are just barely touching
			if (collision.penetration <= 0.0f) {
				continue;
			}

			// Objects displacement is proportional to mass (e.g. A boulder bouncing off a mountain)
			Vec2 displacementPerInverseMass = collision.collisionNormal.Scale(collision.penetration * totalInverseMass);
			transforms.Get(entityA)->position = transforms.Get(entityA)->position + displacementPerInverseMass.Scale(bodies.Get(entityA)->inverseMass);
			transforms.Get(entityB)->position = transforms.Get(entityB)->position + displacementPerInverseMass.Scale(bodies.Get(entityB)->inverseMass);
		} // else { maybe collider exists but no physics body. eg. a kill box or something }
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
				if ( body.velocity.Length() < 2.0f ) {
					body.SetVelocity( Vec2( 0.0f, 0.0f ) );
				}
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