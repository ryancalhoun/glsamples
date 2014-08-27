#include "building.h"
#include<math.h>

int id;

void init_south_end(float upper[][3], float inner[][3], float outer[][3], int wire)
{
	int i,j;

	int gl_fill;

	float normal[3];
	float left_cap[3][3] = {
		{ inner[0][0], inner[0][1], inner[0][2] },
		{ outer[0][0], outer[0][1], outer[0][2] },
		{ upper[0][0], upper[0][1], upper[0][2] },
	};
	float right_cap[3][3] = {
		{ outer[20][0], outer[20][1], outer[20][2] },
		{ inner[20][0], inner[20][1], inner[20][2] },
		{ upper[20][0], upper[20][1], upper[20][2] },
	};

	if(wire)
		gl_fill = GL_LINE_LOOP;
	else 
		gl_fill = GL_POLYGON;

	for(i = 0,j = 1; i < 20; ++i)
	{
		float inside[4][3] = 
		{
			{ inner[j][0], inner[j][1], inner[j][2] },
			{ upper[j][0], 0.6*upper[j][1], upper[j][2] },
			{ upper[i][0], 0.6*upper[i][1], upper[i][2] },
			{ inner[i][0], inner[i][1], inner[i][2] },
		};
		float outside[4][3] = 
		{
			{ outer[j][0], outer[j][1], outer[j][2] },
			{ outer[i][0], outer[i][1], outer[i][2] },
			{ upper[i][0], 0.6*upper[i][1], upper[i][2] },
			{ upper[j][0], 0.6*upper[j][1], upper[j][2] },
		};
		norm(inside, 4, normal);
		glBegin(gl_fill);
		glNormal3fv(normal);
		glVertex3fv(inside[0]);
		glVertex3fv(inside[1]);
		glVertex3fv(inside[2]);
		glVertex3fv(inside[3]);
		glEnd();
		norm(outside, 4, normal);
		glBegin(gl_fill);
		glNormal3fv(normal);
		glVertex3fv(outside[0]);
		glVertex3fv(outside[1]);
		glVertex3fv(outside[2]);
		glVertex3fv(outside[3]);
		glEnd();

		if(i == 4) j = 15;
		else ++j;
		if(i == 5) i = 14;
	}

	norm(left_cap, 3, normal);
	glBegin(gl_fill);
	glNormal3fv(normal);
	glVertex3fv(left_cap[0]);
	glVertex3fv(left_cap[1]);
	glVertex3fv(left_cap[2]);
	glEnd();

	norm(right_cap, 3, normal);
	glBegin(gl_fill);
	glNormal3fv(normal);
	glVertex3fv(right_cap[0]);
	glVertex3fv(right_cap[1]);
	glVertex3fv(right_cap[2]);
	glEnd();


}

void init_north_end(float upper[][3], float inner[][3], float outer[][3], int wire)
{
	int i;

	int gl_fill;

	float normal[3];
	float left_cap[3][3] = {
		{ inner[0][0], inner[0][1], inner[0][2] },
		{ outer[0][0], outer[0][1], outer[0][2] },
		{ upper[0][0], upper[0][1], upper[0][2] },
	};
	float right_cap[3][3] = {
		{ outer[20][0], outer[20][1], outer[20][2] },
		{ inner[20][0], inner[20][1], inner[20][2] },
		{ upper[20][0], upper[20][1], upper[20][2] },
	};

	if(wire)
		gl_fill = GL_LINE_LOOP;
	else 
		gl_fill = GL_POLYGON;

	for(i = 0; i < 20; ++i)
	{
		float inside[4][3] = 
		{
			{ inner[i+1][0], inner[i+1][1], inner[i+1][2] },
			{ upper[i+1][0], upper[i+1][1]/2, upper[i+1][2] },
			{ upper[i][0], upper[i][1]/2, upper[i][2] },
			{ inner[i][0], inner[i][1], inner[i][2] },
		};
		float outside[4][3] = 
		{
			{ outer[i+1][0], outer[i+1][1], outer[i+1][2] },
			{ outer[i][0], outer[i][1], outer[i][2] },
			{ upper[i][0], upper[i][1]/2, upper[i][2] },
			{ upper[i+1][0], upper[i+1][1]/2, upper[i+1][2] },
		};
		glColor3ub(GRASS);
		norm(inside, 4, normal);
		glBegin(gl_fill);
		glNormal3fv(normal);
		glVertex3fv(inside[0]);
		glVertex3fv(inside[1]);
		glVertex3fv(inside[2]);
		glVertex3fv(inside[3]);
		glEnd();
		glColor3ub(STONE);
		norm(outside, 4, normal);
		glBegin(gl_fill);
		glNormal3fv(normal);
		glVertex3fv(outside[0]);
		glVertex3fv(outside[1]);
		glVertex3fv(outside[2]);
		glVertex3fv(outside[3]);
		glEnd();
	}
	norm(left_cap, 3, normal);
	glBegin(gl_fill);
	glNormal3fv(normal);
	glVertex3fv(left_cap[0]);
	glVertex3fv(left_cap[1]);
	glVertex3fv(left_cap[2]);
	glEnd();

	norm(right_cap, 3, normal);
	glBegin(gl_fill);
	glNormal3fv(normal);
	glVertex3fv(right_cap[0]);
	glVertex3fv(right_cap[1]);
	glVertex3fv(right_cap[2]);
	glEnd();

}


void init_side(int direction, float a[][3], float b[][3], float c[][3], float d[][3], int wire)
{
	float face[4][3] = 
	{
		{ a[0][0], a[0][1], a[0][2] + 160 * direction }, 
		{ b[0][0], b[0][1], b[0][2] + 160 * direction },
		{ c[20][0], c[20][1], c[20][2] - 160 * direction },
		{ d[20][0], d[20][1], d[20][2] - 160 * direction },
	};

	float normal[3];

	norm(face, 4, normal);
	if(wire)
		glBegin(GL_LINE_LOOP);
	else
		glBegin(GL_QUADS);

	glNormal3fv(normal);
	glVertex3fv(face[0]);
	glVertex3fv(face[1]);
	glVertex3fv(face[2]);
	glVertex3fv(face[3]);
	glEnd();

}

void init_field(float north[][3], float south[][3], int wire)
{
	int i;
	if(wire)
		glBegin(GL_LINE_LOOP);
	else
		glBegin(GL_POLYGON);

	glNormal3f(0, 1, 0);
	for(i = 0; i < 21; ++i)
		glVertex3f(north[i][0],north[i][1], north[i][2] + 160);

	for(i = 0; i < 21; ++i)
	{
		glVertex3f(south[i][0], south[i][1], south[i][2] - 160);
		if(i == 5) i = 14;
	}

	glEnd();

}



void init_faurot(int wire)
{
	int i, j;
	float north_upper[21][3];
	float north_inner[21][3];
	float north_outer[21][3];
	float south_upper[21][3];
	float south_inner[21][3];
	float south_outer[21][3];

	cubefun cube;
	glNewList(id+wire, GL_COMPILE);


	if(wire)
	{
		cube = glutWireCube;
	}
	else
	{
		cube = glutSolidCube;
	}

	for(i = 0; i < 21; ++i)
	{
		float angle = (i * 9) * 3.14159 / 180;

		north_outer[i][0] = north_upper[i][0] = 200 * cos(angle);
		north_inner[i][0] = 100 * cos(angle);
		north_outer[i][2] = north_upper[i][2] = 200 * sin(angle);
		north_inner[i][2] = 100 * sin(angle); 

		south_outer[20-i][0] = south_upper[20-i][0] = north_upper[i][0];
		south_inner[20-i][0] = north_inner[i][0];
		south_outer[20-i][2] = south_upper[20-i][2] = -north_upper[i][2];
		south_inner[20-i][2] = -north_inner[i][2];

		south_outer[20-i][1] = north_outer[i][1] = 
			south_inner[20-i][1] = north_inner[i][1] = 0;
		south_upper[20-i][1] = north_upper[i][1] = 80;

	}

	glPushMatrix();
	glTranslatef(800, 0, -1000);
	glRotatef(-20, 0, 1, 0);

	glColor3ub(STONE);
	// north endzone
	glPushMatrix();
	glTranslatef(0, 0, 160);
	init_north_end(north_upper, north_inner, north_outer, wire);
	glPopMatrix();

	// south endzone
	glPushMatrix();
	glTranslatef(0, 0, -160);
	init_south_end(south_upper, south_inner, south_outer, wire);
	glPopMatrix();

	// west side
	init_side(1, north_inner, north_upper, south_upper, south_inner, wire);
	init_side(-1, north_outer, north_upper, south_upper, south_outer, wire);

	// east side
	init_side(-1, south_inner, south_upper, north_upper, north_inner, wire);
	init_side(1, south_outer, south_upper, north_upper, north_outer, wire);

	glColor3ub(GRASS);
	// field
	init_field(north_inner, south_inner, wire);

	glColor3ub(BRICK);
	// box
	glPushMatrix();
	glTranslatef(225, 60, 0);
	glScalef(50, 120, 180);
	cube(1);
	glPopMatrix();

	glColor3ub(STONE);
	glPushMatrix();
	glTranslatef(225, 135, 0);
	glScalef(50, 30, 180);
	cube(1);
	glPopMatrix();

	glPopMatrix();
	glEndList();
}

public void init()
{
	id = glGenLists(2);

	init_faurot(0);
	init_faurot(1);

}

public void draw(int wire)
{
	glCallList(id + (wire>0));
}

