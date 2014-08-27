#include "building.h"

int id;

void init_roof(int wire)
{
	float left_left[4][3] = {{-100,30,60},{-80,40,40},{-80,40,-10},{-100,30,-30}};
	float left_right[4][3] = {{-40,30,30},{-60,40,10},{-60,40,40},{-40,30,60}};
	float left_front[4][3] = {{-40,30,60},{-60,40,40},{-80,40,40},{-100,30,60}};

	float right_left[4][3] = {{40,30,60},{60,40,40},{60,40,10},{40,30,30}};
	float right_right[4][3] = {{100,30,-30},{80,40,-10},{80,40,40},{100,30,60}};
	float right_front[4][3] = {{100,30,60},{80,40,40},{60,40,40},{40,30,60}};

	float front[4][3] = {{40,30,30},{60,40,10},{-60,40,10},{-40,30,30}};
	float back[4][3] = {{-100,30,-30},{-80,40,-10},{80,40,-10},{100,30,-30}};

	float lend_left[4][3] = {{-100,30,-40},{-100,30,-30},{-90,35,-20},{-90,35,-30}};
	float lend_right[4][3] = {{-80,30,-30},{-80,30,-40},{-90,35,-30},{-90,35,-20}};
	float lend_back[4][3] = {{-80,30,-40},{-100,30,-40},{-90,35,-30}};

	float rend_left[4][3] = {{80,30,-40},{80,30,-30},{90,35,-20},{90,35,-30}};
	float rend_right[4][3] = {{100,30,-30},{100,30,-40},{90,35,-30},{90,35,-20}};
	float rend_back[4][3] = {{100,30,-40},{80,30,-40},{90,35,-30}};

	float top[4][3] = {{-60,40,-10},{-60,40,10},{60,40,10},{60,40,-10}};
	float left_top[4][3] = {{-80,40,-10},{-80,40,40},{-60,40,40},{-60,40,-10}};
	float right_top[4][3] = {{60,40,-10},{60,40,40},{80,40,40},{80,40,-10}};

	float dleft[4][3] = {{-15,30,-40},{-15,30,-30},{0,40,-10},{0,40,-40}};
	float dright[4][3] = {{15,30,-30},{15,30,-40},{0,40,-40},{0,40,-10}};

	float dback[3][3] = {{15,30,-40},{-15,30,-40},{0,40,-40}};

	struct {
		float* face;
		int sides;
	} faces[] = {
		{(float*)left_left,4},{(float*)left_right,4},
		{(float*)left_front,4},
		{(float*)right_left,4},{(float*)right_right,4},
		{(float*)right_front,4},
		{(float*)front,4},{(float*)back,4},
		{(float*)top,4},
		{(float*)left_top,4},{(float*)right_top,4},
		{(float*)lend_left,4},{(float*)lend_right,4},
		{(float*)rend_left,4},{(float*)rend_right,4},
		{(float*)lend_back,3},{(float*)rend_back,3},
		{(float*)dleft,4},{(float*)dright,4},
		{(float*)dback,3},
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

	for(i = 0; i < 20; i++)
	{
		norm((float**)faces[i].face, faces[i].sides, normal);
		if(i < 19)
			glColor3ub(SLATE);
		else
			glColor3ub(STONE);
		glBegin(gl_wire);
		glNormal3fv(normal);
		for(j = 0; j < faces[i].sides; j++)
			glVertex3fv(faces[i].face + j*3);
		glEnd();
	}
}

void init_townsend(int wire)
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
	glTranslatef(257, 0, 850);

	// 200 x 90
	// 60 x 90 high
	// 80 x 60 high
	// 80 x 50 low

	// bottom
	glColor3ub(STONE);
	glPushMatrix();
	glTranslatef(0, 7, 0);
	glScalef(80, 14, 60);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(70, 7, 15);
	glScalef(60, 14, 90);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-70, 7, 15);
	glScalef(60, 14, 90);
	cube(1);
	glPopMatrix();

	// low part
	glColor3ub(BRICK); 
	glPushMatrix();
	glTranslatef(0, 11, 55);
	glScalef(80, 22, 50);
	cube(1);
	glPopMatrix();

	// high part 
	glPushMatrix();
	glTranslatef(0, 22, 0);
	glScalef(80, 16, 60);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(70, 22, 15);
	glScalef(60, 16, 90);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-70, 22, 15);
	glScalef(60, 16, 90);
	cube(1);
	glPopMatrix();

	// ends
	glPushMatrix();
	glTranslatef(-90, 22, -35);
	glScalef(20, 16, 10);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(90, 22, -35);
	glScalef(20, 16, 10);
	cube(1);
	glPopMatrix();


	// door
	glColor3ub(STONE);
	glPushMatrix();
	glTranslatef(0, 15, -35);
	glScalef(30, 30, 10);
	cube(1);
	glPopMatrix();

	// ends
	glPushMatrix();
	glTranslatef(-90, 7, -35);
	glScalef(20, 14, 10);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(90, 7, -35);
	glScalef(20, 14, 10);
	cube(1);
	glPopMatrix();
	init_roof(wire);

	glPopMatrix();
	glEndList();
}

public void init()
{
	id = glGenLists(2);

	init_townsend(0);
	init_townsend(1);
}

public void draw(int wire)
{
	glCallList(id + (wire>0));
}

