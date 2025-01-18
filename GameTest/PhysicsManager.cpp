#include "stdafx.h"

#include "PhysicsManager.h"

PhysicsManager::PhysicsManager(ECS &ecs) : ecs(ecs) {

}


void PhysicsManager::Integrate(const float deltaTime) {
	ComponentPool<PhysicsBodyComponent>& bodies = *ecs.GetPool<PhysicsBodyComponent>();
	ComponentPool<TransformComponent>& transforms = *ecs.GetPool<TransformComponent>();

	for (int i = 0; i < bodies.dense.size(); i++) {
		EntityID id = bodies.mirror[ i ];
		if ( ecs.HasAllComponents<PhysicsBodyComponent, TransformComponent>( id ) ) {
			PhysicsBodyComponent& body = bodies.dense[i];
			TransformComponent& transform = *transforms.Get( id );
			if (body.inverseMass > 0.0f)
			{
				transform.position += body.velocity.Scale( deltaTime );

				body.acceleration.Zero();
				body.acceleration += body.forceAccumulation.Scale( body.inverseMass );

				body.velocity += body.acceleration.Scale( deltaTime );
				body.velocity = body.velocity.Scale( powf( body.damping, deltaTime ) );

				body.forceAccumulation.Zero();
			}
		}
	}
}