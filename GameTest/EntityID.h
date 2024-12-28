#pragma once

#include <cstdint>

struct EntityID
{
	uint32_t		identifier;

						EntityID();
						EntityID(const uint16_t id, const uint16_t version);

	bool				operator==(const EntityID& other) const;
	uint16_t			GetHandle() const;
	uint16_t			GetVersion() const;
};