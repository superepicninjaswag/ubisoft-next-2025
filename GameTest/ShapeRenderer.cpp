#include "stdafx.h"
#include "ShapeRenderer.h"

ShapeRenderer::ShapeRenderer(ECS& ecs) : ecs(ecs) {

}

void ShapeRenderer::RenderShapes() {
	ComponentPool<ShapeComponent>* shapes = ecs.GetPool<ShapeComponent>();
	ComponentPool<TransformComponent>* transforms = ecs.GetPool<TransformComponent>();

	for (int i = 0; i < shapes->dense.size(); i++) {
		EntityID currentEntity = shapes->mirror[i];					// Which entity are we drawing?
		std::vector<Vec2>& points = shapes->dense[i].points;		// Cache it's points
		for (int j = 0; j < points.size(); j++) {
			// The last point should connect to the first point so we use Modulus
			int k = (j + 1) % points.size();

			// Don't want to modify so we copy
			Vec2 point1 = points[j];
			Vec2 point2 = points[k];

			// We don't use rotation, and scale is baked into ShapeComponent construction

			point1 += transforms->Get(currentEntity)->position;
			point2 += transforms->Get(currentEntity)->position;

			App::DrawLine(point1.x, point1.y, point2.x, point2.y);
		}
	}
}
