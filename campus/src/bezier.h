#ifndef BEZIER_H
#define BEZIER_H

#include "point.h"


struct bezier_curve
{
	point* path;
	point* look;
	int length;
};

extern struct bezier_curve* curve;
extern int bez_curves;
extern int current_bezier_curve;

void bezier_curve(point start, point end, point* ctrl, point* path, int n, int m);
void load_bezier_curves();
void close_bezier();

#endif
