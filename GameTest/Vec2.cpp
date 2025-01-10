#include "stdafx.h"

#include "Vec2.h"


Vec2::Vec2() : x( 0.0f ), y( 0.0f ) {

}

Vec2::Vec2( const float x, const float y ) : x( x ), y( y ) {
}

Vec2 Vec2::operator+( const Vec2& i ) {
	return Vec2(x + i.x, y + i.y);
}

void Vec2::operator+=(const Vec2& i) {
	x += i.x;
	y += i.y;
}
