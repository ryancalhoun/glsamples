#pragma once

#include "color.h"

struct moon
{
	float r;
	float d;
	float a;
	float p;
	struct color c;
};

int setMoonAttr(struct moon* m, char* k, char* v);
void drawMoon(struct moon* m, GLUquadric* q);

