#pragma once


#include <cassert>
#include <utility>
#include <vector>
#include <algorithm>

#include "./EntityID.h"

/*
===============================================================================

	An object pool for components.
	Under the hood it operates as a "sparse set" data structure to manage the components.
	Learn more here: https://skypjack.github.io/2020-08-02-ecs-baf-part-9/

===============================================================================
*/
template<typename T>
class ComponentPool : public ComponentPoolBase {
public:
	std::vector<uint16_t>		sparse;
	std::vector<T>				dense;
	std::vector<EntityID>		mirror;

								ComponentPool();

	void						Init(uint16_t size);
	T *							Get(EntityID id);
	bool						Has(EntityID id);
	void						Delete(EntityID id);

	template <typename... Args>
	void						Add(EntityID id, Args&&... args);
};

template<typename T>
inline ComponentPool<T>::ComponentPool() {
	sparse.resize( UINT16_MAX, 0 );
	mirror.resize( UINT16_MAX, EntityID(0, 0) );
}

template<typename T>
inline void ComponentPool<T>::Init(uint16_t size) {
	dense.reserve(size);
}

template<typename T>
inline T* ComponentPool<T>::Get(EntityID id) {
	assert(this->Has(id));
	return &dense[ sparse[ id.GetHandle() ] ];
}

template<typename T>
inline bool ComponentPool<T>::Has(EntityID id) {
	return mirror[ sparse[ id.GetHandle() ] ] == id;
}

template<typename T>
inline void ComponentPool<T>::Delete(EntityID id) {
	if ( this->Has(id) ) {
		uint16_t index = sparse[ id.GetHandle() ];
		mirror[ index ].Zero();

		if ( dense.size() > 1) {
			std::swap( dense.back(), dense[ index ] );
			std::swap( mirror.back(), mirror[ index ] );
			sparse[ mirror[ index ].GetHandle() ] = index;
		}

		dense.pop_back();
	}
}

template<typename T>
template <typename... Args>
inline void ComponentPool<T>::Add(EntityID id, Args&&... args) {
	dense.emplace_back( std::forward<Args>(args)... );
	sparse[ id.GetHandle() ] = static_cast<uint16_t>( dense.size() - 1 );
	mirror[ dense.size() - 1 ] = id;
}
