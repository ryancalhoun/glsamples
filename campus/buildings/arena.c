#include "building.h"

int id;

void init_dome(GLUquadricObj* q, int wire)
{
	float front_arch[10][3];
	float back_arch[10][3];

	float lf_face[3][3] = {{-150,30,175},{-100,30,175},{-100,70,175}};
	float rf_face[3][3] = {{150,30,175},{100,70,175},{100,30,175}};
	float lb_face[3][3] = {{-150,30,-175},{-100,70,-175},{-100,30,-175}};
	float rb_face[3][3] = {{150,30,-175},{100,30,-175},{100,70,-175}};

	float ls_face[4][3] = {{-150,30,175},{-150,30,-175},{-100,70,-175},{-100,70,175}};
	float rs_face[4][3] = {{100,70,175},{150,30,175},{150,30,-175},{100,70,-175}};

	float li_face[4][3] = {{-100,30,175},{-100,30,-175},{-100,70,-175},{-100,70,175}};
	float ri_face[4][3] = {{100,30,175},{100,30,-175},{100,70,-175},{100,70,175}};

	struct {
		float* face;
		int sides;
	} faces[] = {
		{(float*)lf_face,3}, {(float*)rf_face,3}, 
		{(float*)lb_face,3}, {(float*)rb_face,3},
		{(float*)ls_face,4}, {(float*)rs_face,4},
		{(float*)li_face,4}, {(float*)ri_face,4},
	};

	int i,j; 

	float normal[3];

	int gl_wire, glu_wire;
	if(wire)
	{ 
		gl_wire = GL_LINE_LOOP;
		glu_wire = GLU_LINE;
	}
	else
	{
		gl_wire = GL_POLYGON;
		glu_wire = GLU_FILL;
	}
	gluQuadricDrawStyle(q, glu_wire);

	glPushMatrix();
	glTranslatef(0, 52, -150);
	glScalef(1, .4, 1);
	gluCylinder(q, 110, 110, 300, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 52, 150);
	glScalef(1, .4, 1);
	gluDisk(q, 0, 110, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 52, -150);
	glScalef(1, .4, -1);
	gluDisk(q, 0, 110, 20, 20);
	glPopMatrix();

	for(i = 0; i < 8; ++i)
	{
		norm((float**)faces[i].face, faces[i].sides, normal);
		glBegin(gl_wire);
		glNormal3fv(normal);
		for(j = 0; j < faces[i].sides; ++j)
			glVertex3fv(faces[i].face + j*3);
		glEnd();
	}
}

void init_arena(GLUquadricObj* q, int wire)
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
	glTranslatef(1100, 0, -2000);
	glRotatef(-40, 0, 1, 0);

	glColor3ub(BRICK);
	// main
	glPushMatrix();
	glTranslatef(0, 15, 0);
	glScalef(300, 30, 350);
	cube(1);
	glPopMatrix();

	// left side 
	glPushMatrix();
	glTranslatef(-164, 12, 0);
	glScalef(18, 24, 100);
	cube(1);
	glPopMatrix();

	glColor3ub(STONE);
	glPushMatrix();
	glTranslatef(-155, 15, -5);
	glScalef(10, 30, 340);
	cube(1);
	glPopMatrix();

	// back corner
	glPushMatrix();
	glTranslatef(-110, 15, -180);
	glScalef(100, 30, 10);
	cube(1);
	glPopMatrix();

	// front corner
	glPushMatrix();
	glTranslatef(125, 15, 180);
	glScalef(100, 30, 10);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(165, 15, 130);
	glScalef(30, 30, 100);
	cube(1);
	glPopMatrix();

	glColor3ub(SLATE);
	glPushMatrix();
	glTranslatef(0, 40, 0);
	glScalef(200, 20, 350);
	cube(1);
	glPopMatrix();
	init_dome(q, wire);

	glPopMatrix();

	glEndList();
}


public void init()
{
	GLUquadricObj* q = gluNewQuadric();
	id = glGenLists(2);

	init_arena(q, 0);
	init_arena(q, 1);

	gluDeleteQuadric(q);     
}

public void draw(int wire)
{
	glCallList(id + (wire>0));
}

