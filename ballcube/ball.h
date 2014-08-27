#ifndef BALL_H
#define BALL_H
#include "vec.h"
#include "point.h"

typedef struct ball
{
	point p, pnext;
	vec v;
	float r;
	char rgb[3];
} ball;

#endif
