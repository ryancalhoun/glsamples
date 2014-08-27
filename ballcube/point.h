#ifndef POINT_H
#define POINT_H

typedef struct point
{
	union
	{
		struct { float x, y, z; };
		float v[3];
	};
} point;

float ptDistance(point p1, point p2);

#endif


