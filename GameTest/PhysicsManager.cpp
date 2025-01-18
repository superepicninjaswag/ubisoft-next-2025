#include "stdafx.h"

#include "PhysicsManager.h"

PhysicsManager::PhysicsManager(ECS &ecs) : ecs(ecs), timeStep( (1.0f / APP_MAX_FRAME_RATE) ) {

}


/* 
* Comments are a little excessive for this function because I wanted to make sure I didn't mess up
* and also wanted to keep track of everything happening
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

				// Force is only applied as an impulse, so zero it out.
				body.forceAccumulation.Zero();
			}
		}
	}
}