#pragma once


/*
===============================================================================

	A two-dimensional vector that uses floats for it's elements.

===============================================================================
*/
struct Vec2 {
	float		x;
	float		y;

				Vec2();
				Vec2( const float x, const float y );

	Vec2		operator+( const Vec2& i );
	void		operator+=( const Vec2& i );

	void		Set( const float newX, const float newY );
	Vec2		Scale( const float a );
	Vec2		Scale( const float a, const float b );
	void		Normalize();
	void		Zero();
	float		Length();

};