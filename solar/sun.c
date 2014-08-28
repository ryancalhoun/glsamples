#ifdef _WIN32
#include<windows.h>
#endif

#ifdef __APPLE__
#include<OpenGL/glu.h>
#include<OpenGL/gl.h>
#else
#include<GL/glu.h>
#include<GL/gl.h>
#endif

#include<string.h>
#include<stdio.h>
#include<stdlib.h>

#include "sun.h"
#include "planet.h"

int setSunAttr(struct sun* s, char* k, char* v)
{
	if(strstr(k, "radius"))
		s->r = atof(v);
	else if(strstr(k, "color"))
		sscanf(v , "%f,%f,%f", &s->c.r, &s->c.g, &s->c.b);

	else return -1;
	return 0;
}

void drawSun(struct sun* s, GLUquadric* q, int orbit)
{
	int i;
	float e[3];

	e[0] = s->c.r;
	e[1] = s->c.g;
	e[2] = s->c.b;

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor3fv((float*)&s->c);
	glMaterialfv(GL_FRONT, GL_EMISSION, e);
	gluSphere(q, s->r, 200, 200);
	glEnable(GL_LIGHTING);
	for(i = 0; i < s->nplanets; ++i)
	{
		glPushMatrix();
		glTranslatef(s->planets[i].o, 0, 0);
		if(orbit)
		{
			float e[3] = { 0, 0, 0 };
			glColor3f(.5, .5, .5);
			glMaterialfv(GL_FRONT, GL_EMISSION, e);
			glPushMatrix();
			glRotatef(-90, 1, 0, 0);
			gluDisk(q, s->planets[i].d, s->planets[i].d+.5, 50, 20);
			glPopMatrix();
		}
		drawPlanet(&s->planets[i], q, orbit);
		glPopMatrix();
	}
	glPopMatrix();
}

