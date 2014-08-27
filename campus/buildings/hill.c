#include "building.h"

int id;

void init_roof(int wire)
{
	float m_left[4][3] = {{20,30,-50},{0,40,-30},{0,40,30},{20,30,50}};
	float m_right[4][3] = {{-20,30,50},{0,40,30},{0,40,-30},{-20,30,-50}};
	float m_front[3][3] = {{-20,30,50},{20,30,50},{0,40,30}};
	float m_back[3][3] = {{20,30,-50},{-20,30,-50},{0,40,-30}};

	float s_front[4][3] = {{80,30,50},{80,34,40},{-20,34,40},{-20,30,50}};
	float s_back[4][3] = {{-20,30,30},{-20,34,40},{80,34,40},{80,30,30}};

	float s_left[3][3] = {{80,30,50},{80,30,30},{80,34,40}};
	float s_right[3][3] = {{-20,30,30},{-20,30,50},{-20,34,40}};

	struct {
		float* face;
		int sides;
	} faces[] = {
		{(float*)m_left,4}, {(float*)m_right,4}, 
		{(float*)m_front,3},{(float*)m_back,3},
		{(float*)s_front,4},{(float*)s_back,4},
	}, sides[] = {
		{(float*)s_left,3},{(float*)s_right,3},
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
	for(i = 0; i < 6; ++i)
	{
		norm((float**)faces[i].face, faces[i].sides, normal);
		glBegin(gl_wire);
		glNormal3fv(normal);
		for(j = 0; j < faces[i].sides; ++j)
			glVertex3fv(faces[i].face + j*3);
		glEnd();
	}
	glColor3ub(BRICK);
	for(i = 0; i < 2; ++i)
	{
		norm((float**)sides[i].face, sides[i].sides, normal);
		glBegin(gl_wire);
		glNormal3fv(normal);
		for(j = 0; j < sides[i].sides; ++j)
			glVertex3fv(sides[i].face + j*3);
		glEnd();
	}
}

void init_hill(int wire)
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
	glTranslatef(180, 0, 1000);

	glColor3ub(BRICK);

	// middle
	glPushMatrix();
	glTranslatef(0, 15, 0);
	glScalef(40, 30, 100);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(50, 15, 40);
	glScalef(60, 30, 20);
	cube(1);
	glPopMatrix();

	init_roof(wire);

	glPopMatrix();
	glEndList();

}

public void init()
{
	id = glGenLists(2);

	init_hill(0);
	init_hill(1);
}

public void draw(int wire)
{
	glCallList(id + (wire>0));
}

