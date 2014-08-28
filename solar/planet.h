#pragma once

#include "color.h"
struct moon;

struct planet
{
	float r;
	float d;
	float a;
	float p;
	float t;
	float v;
	float g;
	float o;
	struct color c;
	struct moon* moons;
	int nmoons;
};

int setPlanetAttr(struct planet* p, char* k, char* v);
void drawPlanet(struct planet* p, GLUquadric* q, int orbit);

