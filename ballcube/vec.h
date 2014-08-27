#ifndef VEC_H
#define VEC_H
#include "point.h"
typedef point vec;

vec vecComponents(float x, float y, float z);
vec vecReflect(vec v, vec along, int away);
vec normalize(vec c);
vec crossProduct(vec u, vec v);
float dotProduct(vec u, vec v);
float vecMag(vec v);

#endif
