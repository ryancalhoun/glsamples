#include "building.h"

int id;

void init_roof(int wire)
{
	float m_left[4][3] = {{15,30,-25},{0,40,-15},{0,40,15},{15,30,25}};
	float m_right[4][3] = {{-15,30,25},{0,40,15},{0,40,-15},{-15,30,-25}};
	float m_front[3][3] = {{-15,30,25},{15,30,25},{0,40,15}};
	float m_back[3][3] = {{15,30,-25},{-15,30,-25},{0,40,-15}};

	float left[4][3] = {{-8,30,25},{0,36,25},{0,36,-25},{-8,30,-25}};
	float right[4][3] = {{8,30,-25},{0,36,-25},{0,36,25},{8,30,25}};

	float front[3][3] = {{-8,30,25},{8,30,25},{0,36,25}};
	float back[3][3] = {{8,30,-25},{-8,30,-25},{0,36,-25}};

	struct {
		float* face;
		int sides;
	} faces[] = {
		{(float*)m_left,4}, {(float*)m_right,4}, 
		{(float*)m_front,3},{(float*)m_back,3},
		{(float*)left,4}, {(float*)right,4}, 
	}, white[] = {
		{(float*)front,4}, {(float*)back,4}, 
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
	glColor3ub(STONE);
	for(i = 0; i < 2; ++i)
	{
		norm((float**)white[i].face, white[i].sides, normal);
		glBegin(gl_wire);
		glNormal3fv(normal);
		for(j = 0; j < white[i].sides; ++j)
			glVertex3fv(white[i].face + j*3);
		glEnd();
	}
}

void init_swallow(GLUquadricObj* q, int wire)
{
	int glufill;
	cubefun cube;
	glNewList(id+wire, GL_COMPILE);

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
	gluQuadricDrawStyle(q, glufill);

	glColor3ub(BRICK);


	glPushMatrix();
	glTranslatef(-150, 0, 1150);
	glRotatef(90, 0, 1, 0);

	// main
	glPushMatrix();
	glTranslatef(0, 15, 0);
	glScalef(30, 30, 50);
	cube(1); 
	glPopMatrix();

	// left wing
	glPushMatrix();
	glTranslatef(-17.5, 15, 2.5);
	glScalef(5, 30, 25);
	cube(1); 
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-30, 15, -2.5);
	glScalef(20, 30, 35);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-35, 15, -10);
	glScalef(20, 30, 30);
	cube(1);
	glPopMatrix();

	// right wing
	glPushMatrix();
	glTranslatef(17.5, 15, 2.5);
	glScalef(5, 30, 25);
	cube(1); 
	glPopMatrix();

	glPushMatrix();
	glTranslatef(30, 15, -2.5);
	glScalef(20, 30, 35);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(35, 15, -10);
	glScalef(20, 30, 30);
	cube(1);
	glPopMatrix();


	// corners
	glPushMatrix();
	glTranslatef(40, 0, 15);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(q, 5, 5, 40, 8, 5);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-40, 0, 15);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(q, 5, 5, 40, 8, 5);
	glPopMatrix();

	glColor3ub(SLATE);
	glPushMatrix();
	glTranslatef(40, 40, 15);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(q, 5, 0, 10, 8, 5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-40, 40, 15);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(q, 5, 0, 10, 8, 5);
	glPopMatrix();

	// middle
	glPushMatrix();
	glTranslatef(0, 32, 2.5);
	glScalef(40, 4, 25);
	cube(1); 
	glPopMatrix();

	// left wing
	glPushMatrix();
	glTranslatef(-30, 32, -2.5);
	glScalef(20, 4, 35);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-35, 32, -10);
	glScalef(20, 4, 30);
	cube(1);
	glPopMatrix();

	// right wing
	glPushMatrix();
	glTranslatef(30, 32, -2.5);
	glScalef(20, 4, 35);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(35, 32, -10);
	glScalef(20, 4, 30);
	cube(1);
	glPopMatrix();

	init_roof(wire);

	glPopMatrix();


	glEndList();
}

public void init()
{
	GLUquadricObj* q = gluNewQuadric();
	id = glGenLists(2);
	gluQuadricNormals(q, GLU_FLAT);

	init_swallow(q, 0);
	init_swallow(q, 1);

	gluDeleteQuadric(q);
}

public void draw(int wire)
{
	glCallList(id + (wire>0));
}


