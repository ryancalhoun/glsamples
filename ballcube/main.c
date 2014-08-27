#ifdef _WIN32
#include <windows.h>
typedef void (APIENTRY* ballfun)(double,int,int);
#else
typedef void (* ballfun)(double,int,int);
#endif
#include "point.h"
#include "vec.h"
#include "ball.h"
#include "wall.h"

#include <stdlib.h>
#include <GL/glut.h>

int width, height;
int wire = 0;

// bounding box
wall walls[6] = {
	{ {-50,  0,  0}, { 1, 0, 0}},
	{ { 50,  0,  0}, {-1, 0, 0}},
	{ {  0,-50,  0}, { 0, 1, 0}},
	{ {  0, 50,  0}, { 0,-1, 0}},
	{ {  0,  0,-50}, { 0, 0, 1}},
	{ {  0,  0, 50}, { 0, 0,-1}},
};
int wallsize = 100;

ball balls[10];
int nballs = 0;
float vmax = 2;

float rot = 0;

void loop(int n)
{
	int i, j;
	float c, s;

	for(i = 0; i < nballs; ++i)
	{
		balls[i].pnext.x = balls[i].p.x + balls[i].v.x; 
		balls[i].pnext.y = balls[i].p.y + balls[i].v.y; 
		balls[i].pnext.z = balls[i].p.z + balls[i].v.z; 
	}

	for(i = 0; i < nballs; ++i)
	{ 
		for(j = i+1; j < nballs; ++j)
		{
			if(i != j)
				bbCollide(&balls[i], &balls[j]);
		}
		for(j = 0; j < 6; ++j)
			bwCollide(&balls[i], &walls[j]);

	}

	for(i = 0; i < nballs; ++i)
	{ 
		balls[i].p.x += balls[i].v.x; 
		balls[i].p.y += balls[i].v.y; 
		balls[i].p.z += balls[i].v.z; 
	}
	if(nballs > -1)
		glutTimerFunc(10, loop, n);
	glutPostRedisplay();

	rot += 0.05;
	if(rot > 360)
		rot = 0;
}

void display()
{
	int i = 0;

	float pos0[] = { 100, 50, 20 };
	float pos1[] = { -100, 100, 0 };
	float pos2[] = { 500, 10, -50 };

	ballfun drawball = wire ? glutWireSphere : glutSolidSphere;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40, (float)width/height, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(100, 120, 200, 0, 0, 0, 0, 1, 0);

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glRotatef(rot, 0, 1, 0);

	glLightfv(GL_LIGHT0, GL_POSITION, pos0);
	glLightfv(GL_LIGHT1, GL_POSITION, pos1);
	glLightfv(GL_LIGHT2, GL_POSITION, pos2);

	// draw bounding box
	glDisable(GL_LIGHTING); 
	glColor4ub(255, 255, 255, 255);
	glutWireCube(100);
	glEnable(GL_LIGHTING);

	// draw balls
	if(!wire)
		glColor4ub(255, 0, 0, 255);
	do
	{
		glPushMatrix();
		glTranslatef(balls[i].p.x, balls[i].p.y, balls[i].p.z);
		drawball(balls[i].r, 20, 20);
		glPopMatrix();
		if(!wire)
			glColor4ub(0, 0, 255, 255);
	} while(++i < nballs);

	// shade bounding box
	if(!wire)
	{ 
		glEnable(GL_BLEND);
		glDepthMask(GL_FALSE);
		glColor4ub(255, 255, 255, 50);
		glutSolidCube(100);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}

	glFlush();
	glutSwapBuffers();
}

void reshape(int x, int y)
{
	glViewport(0, 0, x, y);
	width = x;
	height = y;
	glutPostRedisplay();
}

void cleanup()
{
	nballs = -1;
}

void setBallNumber(int n)
{
	if(n < nballs) nballs = n;
	else while(nballs < n)
	{
		balls[nballs].p.x = (rand() % wallsize) - wallsize/2;
		balls[nballs].p.y = (rand() % wallsize) - wallsize/2;
		balls[nballs].p.z = (rand() % wallsize) - wallsize/2;

		balls[nballs].v.x = vmax * (((float)(rand()%100))/100 - 0.5);
		balls[nballs].v.y = vmax * (((float)(rand()%100))/100 - 0.5);
		balls[nballs].v.z = vmax * (((float)(rand()%100))/100 - 0.5);
		balls[nballs].r = 5;

		++nballs;
	}
}

void keyboard(unsigned char key)
{
	if(isdigit(key))
	{
		if(key == '0')
			key = '9' + 1;
		setBallNumber(key-0x30);
		return;
	}

	switch(key)
	{
		case 27: 
		case 'q':
			exit(0);
			break;

		case 'w':
			wire = !wire;
			break;
	}
}

void init()
{
	float light0_diff[] = { .7, .7, .9, 1 };
	float light1_diff[] = { .6, .6, .8, 1 };
	float light2_diff[] = { .4, .4, .6, 1 };

	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diff);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diff);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diff);

	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
	glutCreateWindow("Bouncing Balls");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	init();
	setBallNumber(1);
	loop(0);
	atexit(cleanup);
	glutFullScreen();
	glutMainLoop();

	return 0;
}

