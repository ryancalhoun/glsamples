#pragma once

#include "color.h"
struct planet;

struct sun
{
	float r;
	struct color c;
	struct planet* planets;
	int nplanets;
};

int setSunAttr(struct sun* s, char* k, char* v);
void drawSun(struct sun* s, GLUquadric* q, int orbit);

