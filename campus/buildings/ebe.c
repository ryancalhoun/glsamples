#include "building.h"

int id;

void init_roof(int wire)
{
	float front[4][3] = {{-140.5,40,132},{-124,52,122},{-124,52,42},{-140.5,40,32}};
	float back[4][3] = {{-107.5,40,32},{-124,52,42},{-124,52,122},{-107.5,40,132}};
	float left[3][3] = {{-107.5,40,32},{-140.5,40,32},{-124,52,42}};
	float right[3][3] = {{-140.5,40,132},{-107.5,40,132},{-124,52,122}};

	float sleft[4][3] = {{-130.5,40,65},{-130.5,52,82},{-105,52,82},{-95,40,65}};
	float sright[4][3] = {{-95,40,99},{-105,52,82},{-130.5,52,82},{-130.5,40,99}};
	float sback[3][3] = {{-95,40,99},{-95,40,65},{-105,52,82}};

	float tfront[3][3] = {{-140.5,60,76},{-140.5,60,88},{-134.5,80,82}};
	float tback[3][3] = {{-128.5,60,88},{-128.5,60,76},{-134.5,80,82}};
	float tleft[3][3] = {{-128.5,60,76},{-140.5,60,76},{-134.5,80,82}};
	float tright[3][3] = {{-140.5,60,88},{-128.5,60,88},{-134.5,80,82}};

	float lfront[4][3] = {{-108,40,-99.5},{-108,40,-0.5},{-93,52,-10.5},{-93,52,-89.5}};
	float lback[4][3] = {{-78,40,-99.5},{-93,52,-89.5},{-93,52,-10.5},{-78,40,-0.5}};
	float lleft[3][3] = {{-78,40,-99.5},{-108,40,-99.5},{-93,52,-89.5}};
	float lright[3][3] = {{-108,40,-0.5},{-78,40,-0.5},{-93,52,-10.5}};

	// -115 +- 17, -50 +- 16.5
	float ofront[3][3] = {{-132,40,-66.5},{-132,40,-33.5},{-122,52,-50}};
	float oleft[4][3] = {{-108,40,-66.5},{-132,40,-66.5},{-122,52,-50},{-93,52,-50}};
	float oright[4][3] = {{-132,40,-33.5},{-108,40,-33.5},{-93,52,-50},{-122,52,-50}};

	struct {
		float* face;
		int sides;
	} faces[] = {
		{(float*)front,4},{(float*)back,4},
		{(float*)left,3},{(float*)right,3},
		{(float*)sleft,4},{(float*)sright,4},
		{(float*)sback,3},
		{(float*)tfront,3},{(float*)tback,3},
		{(float*)tleft,3},{(float*)tright,3},
		{(float*)lfront,4},{(float*)lback,4},
		{(float*)lleft,3},{(float*)lright,3},
		{(float*)ofront,3},
		{(float*)oleft,4},{(float*)oright,4},
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
	for(i = 0; i < 18; ++i)
	{
		norm((float**)faces[i].face, faces[i].sides, normal);
		glBegin(gl_wire);
		glNormal3fv(normal);
		for(j = 0; j < faces[i].sides; ++j)
			glVertex3fv(faces[i].face + j*3);
		glEnd();
	}


}


void init_ebe(int wire)
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
	glTranslatef(240, 0, 1200);

	glColor3ub(BRICK);

	// middle
	glPushMatrix();
	glTranslatef(0, 10, -10);
	glScalef(150, 20, 180);
	cube(1);
	glPopMatrix();

	// quad front right
	glPushMatrix();
	glTranslatef(-42, 10, 99);
	glScalef(133, 20, 66);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-75, 29, 82);
	glScalef(66, 22, 34);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-124, 20, 82);
	glScalef(33, 40, 100);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-55, 30, 93);
	glScalef(40, 20, 90);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-65, 30, 30);
	glScalef(20, 20, 40);
	cube(1);
	glPopMatrix();

	// tower
	glPushMatrix();
	glTranslatef(-134.5, 50, 82);
	glScalef(12, 20, 12);
	cube(1);
	glPopMatrix();


	// quad front left
	glPushMatrix();
	glTranslatef(-76.5, 20, -40);
	glScalef(3, 40, 80);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-93, 20, -50);
	glScalef(30, 40, 99);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-115, 20, -50);
	glScalef(34, 40, 33);
	cube(1);
	glPopMatrix();

	// 6th street
	glPushMatrix();
	glTranslatef(120, 20, -10);
	glScalef(100, 40, 180);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(110, 20, 90);
	glScalef(80, 40, 40);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(141, 20, 94);
	glRotatef(45, 0, 1, 0);
	glScalef(60, 40, 20);
	cube(1);
	glPopMatrix();

	// high part    
	glPushMatrix();
	glTranslatef(110, 25, 120);
	glScalef(140, 50, 20);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80, 25, 70);
	glScalef(20, 50, 90);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(100, 25, 80);
	glScalef(20, 50, 70);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(120, 25, 90);
	glScalef(20, 50, 50);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(140, 25, 100);
	glScalef(20, 50, 30);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(130, 25, 75);
	glRotatef(-45, 0, 1, 0);
	glScalef(120, 50, 20);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(92, 25, 20);
	glRotatef(45, 0, 1, 0);
	glScalef(40, 50, 20);
	cube(1);
	glPopMatrix();


	// flat roofs
	glColor3ub(SLATE);
	glPushMatrix();
	glTranslatef(-55, 41, 93);
	glScalef(40, 2, 90);
	cube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-65, 41, 30);
	glScalef(20, 2, 40);
	cube(1);
	glPopMatrix();

	init_roof(wire);

	glPopMatrix();
	glEndList();

}

public void init()
{
	id = glGenLists(2);

	init_ebe(0);
	init_ebe(1);

}
public void draw(int wire)
{
	glCallList(id + (wire>0));
}

