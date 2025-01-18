#pragma once

#include "ComponentPool.h"
#include "ComponentPoolBase.h"
#include "Components.h"
#include "EntityID.h"
#include "IDManager.h"

#include <typeindex>
#include <unordered_map>
#include <memory>
#include <utility>


/*
===============================================================================

	While this is called the ECS, it's more accurately described as a data holder.
	Just a collection of component pools, an id manager, and some logic for deleting entities.
	Logic is maintained by the scene, renderer, etc.

	TODO: Shared components / Singleton components

===============================================================================
*/
class ECS {
public:
	std::unordered_map<std::type_index, std::unique_ptr<ComponentPoolBase>>			componentPools;
	IDManager																		idManager;


																					ECS();
	void																			Init();
	void																			DeleteEntity(EntityID id);

	template <typename T>
	void																			RegisterComponent();

	template <typename T>
	ComponentPool<T>*																GetPool();

	template<typename FirstType, typename SecondType>
	bool																			HasAllComponents( EntityID id );

	template<typename FirstType, typename SecondType, typename ThirdType>
	bool																			HasAllComponents( EntityID id );
};

template<typename T>
inline void ECS::RegisterComponent() {
	// Why doesn't C++14's unordered_map have a .contains()???
	bool poolDoesNotExist = ( componentPools.find( typeid( T ) ) == componentPools.end() );
	if ( poolDoesNotExist ) {
		componentPools.emplace( typeid(T), std::make_unique<ComponentPool<T>>() );
	}
}

template<typename T>
inline ComponentPool<T>* ECS::GetPool() {
	auto iterator = componentPools.find( typeid(T) );
	assert(iterator != componentPools.end());
	return static_cast<ComponentPool<T> *>( iterator->second.get() );
}

template<typename FirstType, typename SecondType>
inline bool ECS::HasAllComponents( EntityID id ) {
	ComponentPool<FirstType>* firstPool = GetPool<FirstType>();
	ComponentPool<SecondType>* secondPool = GetPool<SecondType>();

	return ( firstPool->Has( id ) ) && ( secondPool->Has( id ) );
}

template<typename FirstType, typename SecondType, typename ThirdType>
inline bool ECS::HasAllComponents( EntityID id ) {
	ComponentPool<FirstType>* firstPool = GetPool<FirstType>();
	ComponentPool<SecondType>* secondPool = GetPool<SecondType>();
	ComponentPool<ThirdType>* thirdPool = GetPool<ThirdType>();

	return ( firstPool->Has( id ) ) && ( secondPool->Has( id ) ) && ( thirdPool->Has( id ) );
}