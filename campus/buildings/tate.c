#include "building.h"

int id;

void init_roof(int wire)
{
	float m_left[4][3] = {{20,28,-50},{0,40,-30},{0,40,30},{20,28,50}};
	float m_right[4][3] = {{-20,28,50},{0,40,30},{0,40,-30},{-20,28,-50}};
	float m_front[3][3] = {{-20,28,50},{20,28,50},{0,40,30}};
	float m_back[3][3] = {{20,28,-50},{-20,28,-50},{0,40,-30}};

	struct {
		float* face;
		int sides;
	} faces[] = {
		{(float*)m_left,4}, {(float*)m_right,4}, 
		{(float*)m_front,3},{(float*)m_back,3},
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
	for(i = 0; i < 4; i++)
	{
		norm((float**)faces[i].face, faces[i].sides, normal);
		glBegin(gl_wire);
		glNormal3fv(normal);
		for(j = 0; j < faces[i].sides; j++)
			glVertex3fv(faces[i].face + j*3);
		glEnd();
	}
}
void init_tate(int wire)
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
	glTranslatef(-170, 0, 800);

	glColor3ub(STONE);

	// bottom
	glPushMatrix();
	glTranslatef(0, 7, 0);
	glScalef(40, 14, 100);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(30, 7, 0);
	glScalef(20, 14, 15);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(70, 7, 0);
	glScalef(60, 14, 40);
	cube(1);
	glPopMatrix();

	glColor3ub(BRICK);
	// top
	glPushMatrix();
	glTranslatef(0, 21, 0);
	glScalef(40, 14, 100);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(30, 21, 0);
	glScalef(20, 14, 15);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(70, 21, 0);
	glScalef(60, 14, 40);
	cube(1);
	glPopMatrix();

	glColor3ub(SLATE);
	glPushMatrix();
	glTranslatef(70, 30, 0);
	glScalef(60, 4, 40);
	cube(1);
	glPopMatrix();

	init_roof(wire);

	glPopMatrix();
	glEndList();

}

public void init()
{

	id = glGenLists(2);

	init_tate(0);
	init_tate(1);
}

public void draw(int wire)
{
	glCallList(id + (wire>0));
}

