#include "stdafx.h"

#include "Vec2.h"
#include <cmath>


Vec2::Vec2() : x( 0.0f ), y( 0.0f ) {

}

Vec2::Vec2( const float x, const float y ) : x( x ), y( y ) {
}

Vec2 Vec2::operator+( const Vec2& i ) {
	return Vec2( x + i.x, y + i.y );
}

Vec2 Vec2::operator-(const Vec2& i) {
	return Vec2( x - i.x, y - i.y );
}

void Vec2::operator+=(const Vec2& i) {
	x += i.x;
	y += i.y;
}

void Vec2::Set( const float newX, const float newY ) {
	this->x = newX;
	this->y = newY;
}

Vec2 Vec2::Scale(const float a) {
	return Vec2( x * a, y * a );
}

Vec2 Vec2::Scale( const float a, const float b ) {
	return Vec2( x * a, y * b );
}

void Vec2::Normalize() {
	float length = Length();
	x /= length;
	y /= length;
}

void Vec2::Zero() {
	x = 0.0f;
	y = 0.0f;
}

float Vec2::Length() {
	return std::sqrtf( x * x + y * y );
}

float Vec2::DotProduct(const Vec2& a) {
	return ( x * a.x ) + ( y * a.y );
}
