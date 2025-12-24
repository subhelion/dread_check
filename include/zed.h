#pragma once

#pragma warning( disable : 4061 )
#pragma warning( disable : 4062 )
#pragma warning( disable : 4100 )
#pragma warning( disable : 4201 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 4305 )
#pragma warning( disable : 4324 )
#pragma warning( disable : 4365 )
#pragma warning( disable : 4464 )
#pragma warning( disable : 4820 )
#pragma warning( disable : 5219 )
#pragma warning( disable : 5246 )
#pragma warning( disable : 5262 )
#pragma warning( disable : 4577 )

#define _CRT_SECURE_NO_WARNINGS

//

typedef void *handle;
#define noop ((void)0)
#define coal2( a, b ) (a) ? (a) : (b)
#define coal3( a, b, c ) coal2( (a), coal2( (b), (c) ) )

// logic operators

#define not !
#define and &&
#define or  ||

// bitwise logic operators

#define xor ^

// types

// static_assert( sizeof( char      ) == 1 );
// static_assert( sizeof( int       ) == 4 );
// static_assert( sizeof( long long ) == 8 );

//

typedef signed __int8      int8_t;
typedef short              int16_t;
typedef int                int32_t;
typedef long long          int64_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;
typedef unsigned long long size_t;

//

typedef unsigned int uint;
typedef float unorm; // todo
typedef float norm;  // todo

typedef const char *string;

struct size2 { int x, y; };
struct int2  { int x, y; };

// arrays

#define zed_data_in_h    handle data, int data_size, int data_item_size = 0
#define zed_data_in      handle data, int data_size, int data_item_size
#define zed_data( data ) &data, sizeof( data ), sizeof( data[0] )
#define zed_data_thru    data, data_size, data_item_size

#define array_count( array ) _countof( array )
#define array_and_count( array ) array, _countof( array )
#define array_zero( array ) { memset( ( array ), 0, sizeof( array ) ); }

//

#ifdef zed_mode_debug
void zed_die() { __debugbreak(); }
#else
void zed_die() { *(int *)0 = 0xDEAD; }
#endif

//

#ifndef _WIN64
#error incompatible platform
#endif

// math

#include <math.h>

#define math_pi 3.14159265358979323846f
#define ln log

float sign( float x ) {
	if ( x < 0 ) return -1;
	if ( x > 0 ) return  1;
	return 0;
}

float max( float a, float b ) {
	return ( a > b ) ? a : b;
}

float min( float a, float b ) {
	return ( b > a ) ? a : b;
}

float dtor( float degrees ) {
	return degrees * math_pi / 180;
}

float rtod( float radians ) {
	return radians * 180 / math_pi;
}

float converge( float current, float target, float delta ) {
	if ( current < target - delta ) {
		return current + delta;
	} else if ( current > target + delta ) {
		return current - delta;
	}

	return target;
}

float lerp( float a, float b, float t ) {
    return ( 1 - t ) * a + ( t ) * b;
}

float clamp( float x, float x_min = 0.0, float x_max = 1.0 ) {
	return min( max( x, x_min ), x_max );
}
