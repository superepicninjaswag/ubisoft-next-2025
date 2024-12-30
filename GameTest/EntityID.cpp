#include "stdafx.h"

#include "EntityID.h"

EntityID::EntityID() : identifier( 0 ) {

}

EntityID::EntityID(uint16_t handle, uint16_t version) : identifier( ( static_cast<uint32_t>( handle ) << 16 | version ) ) {

}

bool EntityID::operator==(const EntityID& other) const {
	return identifier == other.identifier;
}

uint16_t EntityID::GetHandle() const {
	return static_cast<uint16_t>(identifier >> 16);
}

void EntityID::SetHandle(uint16_t handle) {
	identifier &= 0x0000FFFF;
	identifier |= (static_cast<uint32_t>( handle ) << 16);
}

uint16_t EntityID::GetVersion() const {
	return static_cast<uint16_t>(identifier);
}

void EntityID::SetVersion(uint16_t version) {
	identifier &= 0xFFFF0000;
	identifier |= (static_cast<uint32_t>(version));
}

void EntityID::Zero() {
	identifier = 0;
}
