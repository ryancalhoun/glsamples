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

#include "moon.h"

int setMoonAttr(struct moon* m, char* k, char* v)
{
	float fv = atof(v);
	if(strstr(k, "radius"))
		m->r = fv;
	else if(strstr(k, "distance"))
		m->d = fv;
	else if(strstr(k, "period"))
		m->p = fv; 
	else if(strstr(k, "color"))
		sscanf(v, "%f,%f,%f", &m->c.r, &m->c.g, &m->c.b);
	else return -1;
	return 0;
}

void drawMoon(struct moon* m, GLUquadric* q)
{
	float e[] = { 0, 0, 0, 1 };
	glPushMatrix();
	glRotatef(m->a, 0, 1, 0);
	glTranslatef(m->d, 0, 0);
	glRotatef(m->a, 0, 1, 0);
	glColor3fv((float*)&m->c);
	glMaterialfv(GL_FRONT, GL_EMISSION, e);
	gluSphere(q, m->r, 20, 20);
	glPopMatrix();
}

