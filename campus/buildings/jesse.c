#include "building.h"

int id;

void init_roof(int wire)
{
	// middle
	float front_left[4][3] = {{15,46,50},{0,53,50},{0,53,60},{15,46,60}};
	float front_right[4][3] = {{-15,46,60},{0,53,60},{0,53,50},{-15,46,50}};
	float mid_front[4][3] = {{80,46,20},{80,53,0},{-80,53,0},{-80,46,20}};
	float mid_back[4][3] =  {{80,46,-20},{-80,46,-20},{-80,53,0},{80,53,0}};

	// right
	float right_right[4][3] = {{110,46,-50},{80,64,-20},{80,64,10},{110,46,40}};
	float right_left[4][3] = {{50,46,40},{80,64,10},{80,64,-20},{50,46,-50}};
	float right_front[3][3] = {{110,46,40},{80,64,10},{50,46,40}};
	float right_back[3][3] = {{110,46,-50},{50,46,-50},{80,64,-20}};

	float m_right_right[4][3] = {{100,46,-50},{80,58,-50},{80,58,40},{100,46,40}};
	float m_right_left[4][3] = {{60,46,40},{80,58,40},{80,58,-50},{60,46,-50}};


	// left
	float left_right[4][3] = {{-50,46,-40},{-80,64,-20},{-80,64,20},{-50,46,40}};
	float left_left[4][3] = {{-110,46,40},{-80,64,20},{-80,64,-20},{-110,46,-40}};
	float left_front[3][3] = {{-50,46,40},{-80,64,20},{-110,46,40}};
	float left_back[3][3] = {{-50,46,-40},{-110,46,-40},{-80,64,-20}};

	float m_left_right[4][3] = {{-60,46,-40},{-80,58,-40},{-80,58,40},{-60,46,40}};
	float m_left_left[4][3] = {{-100,46,40},{-80,58,40},{-80,58,-40},{-100,46,-40}};

	// white
	float front[3][3] = {{15,46,60},{0,53,60},{-15,46,60}};
	float m_right_front[3][3] = {{100,46,40},{80,58,40},{60,46,40}};
	float m_right_back[3][3] = {{100,46,-50},{60,46,-50},{80,58,-50}};
	float m_left_front[3][3] = {{-100,46,40},{-60,46,40},{-80,58,40}};
	float m_left_back[3][3] = {{-100,46,-40},{-80,58,-40},{-60,46,-40}};

	struct {
		float* face;
		int sides;
	} faces[] = {
		{(float*)front_left,4}, {(float*)front_right,4},
		{(float*)mid_front,4}, {(float*)mid_back,4}, 
		{(float*)right_right,4},{(float*)right_left,4},
		{(float*)right_front,3},{(float*)right_back,3},
		{(float*)m_right_right,4},{(float*)m_right_left,4},
		{(float*)left_right,4},{(float*)left_left,4},
		{(float*)left_front,3},{(float*)left_back,3},
		{(float*)m_left_right,4},{(float*)m_left_left,4},
	}, white_faces[] = {
		{(float*)front,3},
		{(float*)m_right_front,3},{(float*)m_right_back,3},
		{(float*)m_left_front,3},{(float*)m_left_back,3},
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
	for(i = 0; i < 16; ++i)
	{
		norm((float**)faces[i].face, faces[i].sides, normal);
		glBegin(gl_wire);
		glNormal3fv(normal);
		for(j = 0; j < faces[i].sides; ++j)
			glVertex3fv(faces[i].face + j*3);
		glEnd();
	}

	glColor3ub(STONE);
	for(i = 0; i < 5; ++i)
	{
		norm((float**)white_faces[i].face, white_faces[i].sides, normal);
		glBegin(gl_wire);
		glNormal3fv(normal);
		for(j = 0; j < white_faces[i].sides; ++j)
			glVertex3fv(white_faces[i].face + j*3);
		glEnd();
	}
}
void init_jesse(GLUquadricObj* q, int wire)
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

	glPushMatrix();
	glTranslatef(0, 0, 1000);

	glColor3ub(SLATE);
	glPushMatrix();
	glTranslatef(0, 55, 0);
	glScalef(60, 2, 100);
	cube(1); 
	glPopMatrix();

	glColor3ub(BRICK);

	// main
	glPushMatrix();
	glTranslatef(0, 39, 0);
	glScalef(60, 30, 100);
	cube(1); 
	glPopMatrix();

	// left wing
	glPushMatrix();
	glTranslatef(-40, 34, 0);
	glScalef(20, 24, 40);
	cube(1); 
	glPopMatrix();

	// auditorium
	glPushMatrix();
	glTranslatef(-80, 34, 0);
	glScalef(60, 24, 80);
	cube(1);
	glPopMatrix();

	// right wing
	glPushMatrix();
	glTranslatef(40, 34, 0);
	glScalef(20, 24, 40);
	cube(1); 
	glPopMatrix();

	// offices
	glPushMatrix();
	glTranslatef(80, 34, -5);
	glScalef(60, 24, 90);
	cube(1);
	glPopMatrix();

	// stage
	glPushMatrix();
	glTranslatef(-140, 34, 0);
	glScalef(60, 24, 70);
	cube(1);
	glPopMatrix();

	glColor3ub(SLATE);
	// dome
	glPushMatrix();
	glTranslatef(0, 94, 0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(q, 14, 20, 20);
	glPopMatrix();

	glColor3ub(STONE);
	// spike
	glPushMatrix();
	glTranslatef(0, 54, 0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(q, 15, 15, 40, 10, 5);
	gluCylinder(q, 10, 0, 65, 10, 5);
	glPopMatrix();

	// steps
	glPushMatrix();
	glTranslatef(0, 2, 4);
	glScalef(30, 4, 120);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 1.5, 4);
	glScalef(30, 3, 124);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 1, 4);
	glScalef(30, 2, 128);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.5, 4);
	glScalef(30, 1, 132);
	cube(1);
	glPopMatrix();

	// columns
	glPushMatrix();
	glTranslatef(13, 4, 58);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(q, 2, 2, 42, 10, 5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.33, 4, 58);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(q, 2, 2, 42, 10, 5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4.33, 4, 58);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(q, 2, 2, 42, 10, 5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-13, 4, 58);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(q, 2, 2, 42, 10, 5);
	glPopMatrix();

	// main
	glPushMatrix();
	glTranslatef(0, 12, 0);
	glScalef(60, 24, 100);
	cube(1); 
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 24, 55);
	glScalef(30, 4, 10);
	cube(1); 
	glPopMatrix();

	// left wing
	glPushMatrix();
	glTranslatef(-40, 11, 0);
	glScalef(20, 22, 40);
	cube(1); 
	glPopMatrix();

	// auditorium
	glPushMatrix();
	glTranslatef(-80, 11, 0);
	glScalef(60, 22, 80);
	cube(1);
	glPopMatrix();

	// right wing
	glPushMatrix();
	glTranslatef(40, 11, 0);
	glScalef(20, 22, 40);
	cube(1); 
	glPopMatrix();

	// offices
	glPushMatrix();
	glTranslatef(80, 11, -5);
	glScalef(60, 22, 90);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-140, 11, 0);
	glScalef(60, 22, 70);
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

	init_jesse(q, 0);
	init_jesse(q, 1);

	gluDeleteQuadric(q);
}

public void draw(int wire)
{
	glCallList(id + (wire>0));
}


