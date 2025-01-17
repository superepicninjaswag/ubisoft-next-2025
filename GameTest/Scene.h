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
	virtual void		Load() = 0;
	virtual void		Unload() = 0;
	virtual void		Update() = 0;
	virtual void		Render() = 0;
};