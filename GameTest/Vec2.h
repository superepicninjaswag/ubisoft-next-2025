#pragma once


struct Vec2 {
	float		x;
	float		y;

				Vec2();
				Vec2( const float x, const float y );

	Vec2		operator+( const Vec2& i );
	void		operator+=( const Vec2& i );
};