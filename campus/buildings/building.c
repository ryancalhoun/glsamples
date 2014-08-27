#include "building.h"

void norm(float verts[][3], int sides, float normal[3])
{
	float ax = verts[1][0] - verts[0][0];
	float ay = verts[1][1] - verts[0][1];
	float az = verts[1][2] - verts[0][2];

	float bx = verts[sides-1][0] - verts[0][0];
	float by = verts[sides-1][1] - verts[0][1];
	float bz = verts[sides-1][2] - verts[0][2];

	normal[0] = ay * bz - by * az;
	normal[1] = az * bx - bz * ax;
	normal[2] = ax * by - bx * ay;

}



