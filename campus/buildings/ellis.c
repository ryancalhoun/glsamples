#include "building.h"

int id;

void init_roof(int wire)
{
	// front
	float mid_front[4][3] = {{80,60,120},{80,80,100},{-80,80,100},{-80,60,120}};
	float mid_back[4][3] =  {{80,60,80},{-80,60,80},{-80,80,100},{80,80,100}};

	// right
	float right_right[4][3] = {{100,70,0},{80,85,15},{80,85,125},{100,70,140}};
	float right_left[4][3] = {{60,70,140},{80,85,125},{80,85,15},{60,70,0}};
	float right_front[3][3] = {{100,70,140},{80,85,125},{60,70,140}};
	float right_back[3][3] = {{100,70,0},{60,70,0},{80,85,15}};

	// left
	float left_right[4][3] = {{-60,70,0},{-80,85,15},{-80,85,125},{-60,70,140}};
	float left_left[4][3] = {{-100,70,140},{-80,85,125},{-80,85,15},{-100,70,0}};
	float left_front[3][3] = {{-60,70,140},{-80,85,125},{-100,70,140}};
	float left_back[3][3] = {{-60,70,0},{-100,70,0},{-80,85,15}};

	struct {
		float* face;
		int sides;
	} faces[] = {
		{(float*)mid_front,4}, {(float*)mid_back,4}, 
		{(float*)right_right,4},{(float*)right_left,4},
		{(float*)right_front,3},{(float*)right_back,3},
		{(float*)left_right,4},{(float*)left_left,4},
		{(float*)left_front,3},{(float*)left_back,3},
	};

	int i,j; 

	float normal[3];

	int gl_wire, glu_wire;
	if(wire)
	{ 
		gl_wire = GL_LINE_LOOP;
	}
	else
	{
		gl_wire = GL_POLYGON;
	}

	glColor3ub(SLATE);
	for(i = 0; i < 10; ++i)
	{
		norm((float**)faces[i].face, faces[i].sides, normal);
		glBegin(gl_wire);
		glNormal3fv(normal);
		for(j = 0; j < faces[i].sides; ++j)
			glVertex3fv(faces[i].face + j*3);
		glEnd();
	}
}

void init_ellis(int wire)
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
	glTranslatef(-500, 0, 600);

	glColor3ub(STONE);

	// front
	glPushMatrix();
	glTranslatef(0, 30, 60);
	glScalef(200, 60, 120);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80, 35, 70);
	glScalef(40, 70, 140);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-80, 35, 70);
	glScalef(40, 70, 140);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-125, 35, 60);
	glScalef(50, 70, 120);
	cube(1);
	glPopMatrix();

	// back
	glPushMatrix();
	glTranslatef(-40, 10, -50);
	glScalef(220, 20, 100);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(70, 10, -65);
	glScalef(20, 20, 70);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80, 10, -75);
	glScalef(20, 20, 50);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(90, 10, -95);
	glScalef(20, 20, 30);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-140, 10, -95);
	glScalef(20, 20, 30);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(95, 10, -110);
	glScalef(10, 20, 20);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-145, 10, -110);
	glScalef(10, 20, 20);
	cube(1);
	glPopMatrix();

	// steps
	glPushMatrix();
	glTranslatef(0, 2, 128);
	glScalef(50, 4, 16);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 1.5, 130);
	glScalef(50, 3, 20);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 1, 132);
	glScalef(50, 2, 24);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.5, 134);
	glScalef(50, 1, 28);
	cube(1);
	glPopMatrix();

	// roof
	init_roof(wire);

	glPopMatrix();
	glEndList();

}

public void init()
{
	id = glGenLists(2);

	init_ellis(0);
	init_ellis(1);

}
public void draw(int wire)
{
	glCallList(id + (wire>0));
}

