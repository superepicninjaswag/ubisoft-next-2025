#pragma once

#include <cstdint>

struct EntityID
{
	uint32_t			identifier;

						EntityID();
						EntityID(const uint16_t handle, const uint16_t version);

	bool				operator==(const EntityID& other) const;
	uint16_t			GetHandle() const;
	void				SetHandle(uint16_t handle);
	uint16_t			GetVersion() const;
	void				SetVersion(uint16_t version);
	void				Zero();
};