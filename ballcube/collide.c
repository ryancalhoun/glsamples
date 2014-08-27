#include "vec.h"
#include "point.h"
#include "wall.h"
#include "ball.h"
#include <math.h>

void bbCollide(ball* b1, ball* b2)
{
	vec v;
	float c = ptDistance(b1->p, b2->p);
	float d = ptDistance(b1->pnext, b2->pnext);

	float vc1, vc2;

	v.x = b1->p.x - b2->p.x;
	v.y = b1->p.y - b2->p.y;
	v.z = b1->p.z - b2->p.z;

	v = normalize(v);
	vc1 = dotProduct(b1->v, v); 
	vc2 = dotProduct(b2->v, v); 

	if(d < c && (c - b1->r - b2->r) <= 0)
	{
		b1->v.x -= v.x * (vc1 + vc2);
		b1->v.y -= v.y * (vc1 + vc2);
		b1->v.z -= v.z * (vc1 + vc2);

		b2->v.x -= v.x * (vc2 - vc1);
		b2->v.y -= v.y * (vc2 - vc1);
		b2->v.z -= v.z * (vc2 - vc1);

	}
}

void bwCollide(ball* b, wall* w)
{
	vec u;
	vec v;
	float c;
	float d;

	// vector from plane to ball
	u.x = b->p.x - w->p.x;
	u.y = b->p.y - w->p.y;
	u.z = b->p.z - w->p.z;

	v.x = b->pnext.x - w->p.x;
	v.y = b->pnext.y - w->p.y;
	v.z = b->pnext.z - w->p.z;

	c = dotProduct(u, w->n) / vecMag(w->n); 
	d = dotProduct(v, w->n) / vecMag(w->n); 

	if(d < c && (c - b->r) <= 0)
		b->v = vecReflect(b->v, w->n, 0);
}


