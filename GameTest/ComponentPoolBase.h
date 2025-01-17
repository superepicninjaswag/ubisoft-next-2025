#pragma once


#include <cassert>
#include <utility>
#include <vector>
#include <algorithm>

#include "./EntityID.h"

/*
===============================================================================

	I want an unordered map from ComponentType to the respective pool in my ECS class but,
	I can't define the map from ComponentType to ComponentPool because the latter is templated
	and unique_ptr won't take void because because it doesn't know how to delete that,
	and I don't want to make a hideous templated deleter to go with it.
	Thus, I created a base component pool class that a unique pointer can hold and along
	with it's key, the type for the pool's elements, define templated functions
	for registration and returning the pool with a cast.

===============================================================================
*/
class ComponentPoolBase {
public:
	virtual ~ComponentPoolBase() = default;
};