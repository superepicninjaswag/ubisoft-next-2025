#pragma once

#include "./EntityID.h"


class IDManager {
public:
	uint16_t					nextNewID = 1;
	std::vector<EntityID>		recycledIDs;

	EntityID					GetNewId();
	void						RecycleID(EntityID id);
};