#include "point.h"
#include <math.h>

float ptDistance(point p1, point p2)
{
	float dx = p1.x - p2.x;
	float dy = p1.y - p2.y;
	float dz = p1.z - p2.z;
	return sqrt(dx * dx + dy * dy + dz * dz);
}


