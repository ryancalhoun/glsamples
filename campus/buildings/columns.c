#include "building.h"

#define COLUMNS 6
int id;

void column(GLUquadricObj* q, int i, int wire)
{
	int glufill;
	cubefun cube;

	if(wire)
	{
		glufill = GLU_LINE;
		cube = glutWireCube;
	}
	else
	{
		glufill = GLU_FILL;
		cube = glutSolidCube;
	}

	glColor3ub(STONE);

	gluQuadricDrawStyle(q, glufill);
	glPushMatrix();
	glTranslatef(20*i - 50, 8, 0);
	glRotatef(-90, 1, 0, 0); 
	gluCylinder(q, 4, 3, 40, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20*i - 50, 4, 0);
	glScalef(10, 8, 10);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20*i - 50, 50, 0);
	glScalef(9, 4, 9);
	cube(1);
	glPopMatrix();

}

void init_columns(GLUquadricObj* q, int wire)
{
	int i;
	glNewList(id+wire, GL_COMPILE);

	glPushMatrix();
	glTranslatef(0, 0, 1283);
	for(i = 0; i < COLUMNS; ++i)
		column(q, i, wire);
	glPopMatrix();
	glEndList();
}

public void init()
{
	GLUquadricObj* q = gluNewQuadric();
	id = glGenLists(2);
	gluQuadricNormals(q, GLU_FLAT);

	init_columns(q, 0);
	init_columns(q, 1);

	gluDeleteQuadric(q);
}

public void draw(int wire)
{
	glCallList(id + (wire>0));
}



