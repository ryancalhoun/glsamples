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

#include<math.h>

#include<string.h>
#include<stdio.h>
#include<stdlib.h>

#include "planet.h"
#include "moon.h"

int setPlanetAttr(struct planet* p, char* k, char* v)
{
	float fv = atof(v);

	if(strstr(k, "radius"))
		p->r = fv;
	else if(strstr(k, "distance"))
		p->d = fv;
	else if(strstr(k, "period"))
		p->p = fv; 
	else if(strstr(k, "day"))
		p->v = fv; 
	else if(strstr(k, "tilt"))
		p->t = fv; 
	else if(strstr(k, "rings"))
		p->g = fv; 
	else if(strstr(k, "offset"))
		p->o = fv; 
	else if(strstr(k, "color"))
		sscanf(v, "%f,%f,%f", &p->c.r, &p->c.g, &p->c.b);
	else return -1;
	return 0;
}

void drawPlanet(struct planet* p, GLUquadric* q, int orbit)
{
	int i;
	float e[] = { 0, 0, 0, 1 };
	float x, y, z;

	glPushMatrix();
	glRotatef(p->a, 0, 1, 0);
	glTranslatef(p->d, 0, 0);
	glRotatef(-p->a, 0, 1, 0);
	glRotatef(p->t, 1, 0, 0);

	// planet
	glColor3fv((float*)&p->c);
	glMaterialfv(GL_FRONT, GL_EMISSION, e);
	gluSphere(q, p->r, 20, 20);

	// rings
	if(p->g > 0)
	{
		glColor3f(.9, .9, .9);
		glPushMatrix();
		glTranslatef(0, .1, 0);
		glRotatef(-90, 1, 0, 0);
		gluDisk(q, p->r*1.5, p->r*1.5+p->g, 50, 20);
		glPopMatrix();
		glPushMatrix();
		glRotatef(90, 1, 0, 0);
		gluDisk(q, p->r*1.5, p->r*1.5+p->g, 50, 20);
		glPopMatrix();
	}

	// moons
	for(i = 0; i < p->nmoons; ++i)
	{
		// orbit
		if(orbit)
		{
			glColor3f(.5, .5, .5);
			glPushMatrix();
			glRotatef(-90, 1, 0, 0);
			gluDisk(q, p->moons[i].d, p->moons[i].d+.1, 50, 20);
			glPopMatrix();
		}
		drawMoon(&p->moons[i], q);
	}
	glPopMatrix();
}



