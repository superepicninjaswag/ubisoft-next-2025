#include "stdafx.h"
#include "ECS.h"

ECS::ECS() {

}

void ECS::Init() {
	transforms.Init(300);
	shapes.Init(50);
}

void ECS::DeleteEntity(EntityID id) {
	idManager.RecycleID(id);

	transforms.Delete(id);
	shapes.Delete(id);
}

void ECS::UpdateSystems() {

}

void ECS::DrawShapes() {
	for (int i = 0; i < shapes.dense.size(); i++) {
		std::vector<Vec2>& points = shapes.dense[i].points;
		for (int j = 0; j < points.size(); j++) {
			int k = ( j + 1 ) % points.size();

			Vec2 point1 = points[j];
			Vec2 point2 = points[k];

			EntityID currentEntity = shapes.mirror[i];

			// Scale shape
			Vec2 scale = transforms.Get(currentEntity)->scale;
			point1.x *= 10;
			point1.y *= 10;
			point2.x *= 10;
			point2.y *= 10;

			// Model space to world space
			point1 += transforms.Get(currentEntity)->position;
			point2 += transforms.Get(currentEntity)->position;

			App::DrawLine(point1.x, point1.y, point2.x, point2.y);
		}
	}
}
