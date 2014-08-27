/*
 *  a 3-d point with floating point precision
 *
 */
#ifndef POINT_H
#define POINT_H

typedef struct point
{ 
	union
	{
		struct { float x; float y; float z; };
		float v[3];
	};
} point;

#endif


