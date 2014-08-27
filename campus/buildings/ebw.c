#include "building.h"

int id;

void init_ebw(int wire)
{
	cubefun cube;

	if(wire)
	{
		cube = glutWireCube;
	}
	else
	{
		cube = glutSolidCube;
	}

	glNewList(id+wire, GL_COMPILE);
	glPushMatrix();
	glTranslatef(500, 0, 1330);

	glColor3ub(BRICK);
	// main
	glPushMatrix();
	glTranslatef(60, 20, 30);
	glScalef(120, 40, 60);
	cube(1);
	glPopMatrix();

	// auditorium
	glPushMatrix();
	glTranslatef(25, 10, -35);
	glScalef(40, 20, 30);
	cube(1);
	glPopMatrix();


	glColor3ub(SLATE);
	// entry
	glPushMatrix();
	glTranslatef(25, 8, -10);
	glScalef(30, 16, 20);
	cube(1);
	glPopMatrix();



	glPopMatrix();
	glEndList();
}


public void init()
{
	id = glGenLists(2);

	init_ebw(0);
	init_ebw(1);
}

public void draw(int wire)
{
	glCallList(id + (wire>0));
}
