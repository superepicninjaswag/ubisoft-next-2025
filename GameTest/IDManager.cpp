#include "stdafx.h"

#include "IDManager.h"

EntityID IDManager::GetNewId() {
	EntityID newID;

	if ( recycledIDs.size() > 0 ) {
		newID.SetHandle( recycledIDs.back().GetHandle() );
		newID.SetVersion( recycledIDs.back().GetVersion() );
		recycledIDs.pop_back();
	} else {
		newID.SetHandle( nextNewID++ );
		newID.SetVersion( 0 );
	}

	return newID;
}

void IDManager::RecycleID(EntityID id) {
	recycledIDs.emplace_back( id.GetHandle(), id.GetVersion() + 1 );
}
