/*
 *  Main program, GL and GLUT functions
 *
 */
#ifdef _WIN32
#include<windows.h>
#endif
#include<GL/glut.h>
#include<GL/glu.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
#include "campus.h"
#include "keyboard.h"
#include "camera.h"
#include "buildings/building.h"
#include "bezier.h"

#define PI 3.14159265359


int wire = 0;

/*
 *  top-level redraw display function
 *
 */
void display()
{
	int i, j;
float light0_pos[] = { 200, 700, 1000, 0 };
	float light1_pos[] = { -300, 300, 500, 0 };
	float light2_pos[] = { 100, 100, 300, 0 };

	aim_camera();

	// clear background
	glClearColor(0, 0, 0, 0);
	glShadeModel(GL_SMOOTH);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
	glLightfv(GL_LIGHT2, GL_POSITION, light2_pos);

	for(i = 0; i < campus_building_count; ++i)
	{
		if(campus_buildings[i].draw)
			campus_buildings[i].draw(wire);
	}

	glFlush();
	glutSwapBuffers();
}


/*
 *  handle reshape event
 *
 */
void reshape(int x, int y)
{
	glViewport(0, 0, x, y);
	width = x;
	height = y;

	glutPostRedisplay();
}


/*
 *
 *
 */
void mouse_click(int b, int s, int x, int y)
{
}


/*
 *
 *
 */
void mouse_drag(int x, int y)
{
}


/*
 *  positions and colors of lights
 *
 */
void init_lights()
{

	float light0_pos[] = { 200, 1000, 100, 0 };
	float light1_pos[] = { -300, 200, 300, 0 };

	float light0_diff[] = { .7, .7, .9, 1 };
	float light1_diff[] = { .4, .4, .8, 1 };
	float light2_diff[] = { .4, .4, .6, 1 };

	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diff);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diff);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diff);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
}

void fillMode(int e)
{
	wire = !wire;
	glutPostRedisplay();
}

/*
 *  quiet close and exit
 */
void closeWin(int e)
{
	close_camera();
	close_campus();
	exit(0);
}


/*
 *  Ubiquitous main function, argv and all
 *
 */
int main(int argc, char* argv[])
{
	int bez[] = { 
		GLUT_KEY_F1,
		GLUT_KEY_F2,
		GLUT_KEY_F3,
		GLUT_KEY_F4,
		GLUT_KEY_F5,
		GLUT_KEY_F6,
		GLUT_KEY_F7,
		GLUT_KEY_F8,
		GLUT_KEY_F9,
		0,
	};

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);

	glutCreateWindow("University of Missouri Campus");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse_click);
	glutMotionFunc(mouse_drag);

	// real-time muliple key-presses
	initKeyboard(50);
	keyboardCallbackv("asdfhjklionm", move_camera);
	keyboardCallback(27, closeWin);
	keyboardSpecialCallback(GLUT_KEY_F12, fillMode);
	keyboardSpecialCallback(GLUT_KEY_F11, free_camera);
	keyboardSpecialCallback(GLUT_KEY_F10, circle_camera);
	keyboardSpecialCallbackv(bez, bezier_camera);

	init_lights();
	init_campus();
	init_camera();

	glutFullScreen();
	glutMainLoop();
	return 0;
}


