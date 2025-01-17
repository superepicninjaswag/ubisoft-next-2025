#pragma once


/*
===============================================================================

	Base scene class. Derived classes should implement these functions to define that specific scene
	and create member variables/methods for specific behaviours to that scene
	e.g. UI, rendering, game systems, etc

===============================================================================
*/
class Scene {
public:
	virtual void		load() = 0;
	virtual void		unload() = 0;
	virtual void		update() = 0;
	virtual void		render() = 0;
};