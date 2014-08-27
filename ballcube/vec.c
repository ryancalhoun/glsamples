#include<vec.h>

vec vecComponents(float x, float y, float z)
{
	vec v = { x, y, z };
	return v;
}

vec crossProduct(vec u, vec v)
{
	vec p = {
		u.y * v.z - u.z * v.y,
		u.z * v.x - u.x * v.z,
		u.x * v.y - u.y * v.x
	};
	return p;
}

float dotProduct(vec u, vec v)
{
	return u.x * v.x + u.y * v.y + u.z * v.z;
}

float vecMag(vec v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

vec normalize(vec v)
{
	float d = vecMag(v);
	vec n = {
		v.x / d,
		v.y / d,
		v.z / d
	};
	return n;
}

vec vecReflect(vec v, vec along, int away)
{
	float vc;
	if(!away)
	{
		along.x = -along.x;
		along.y = -along.y;
		along.z = -along.z; 
	}
	along = normalize(along);
	vc = dotProduct(v, along);

	v.x -= 2 * vc * along.x;
	v.y -= 2 * vc * along.y;
	v.z -= 2 * vc * along.z;

	return v;
}


