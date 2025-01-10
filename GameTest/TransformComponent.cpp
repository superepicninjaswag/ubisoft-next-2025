#include "stdafx.h"

#include "TransformComponent.h"


TransformComponent::TransformComponent() {
	scale.x = 1.0f;
	scale.y = 1.0f;
}

TransformComponent::TransformComponent(float x, float y) : position(x, y) {

}
