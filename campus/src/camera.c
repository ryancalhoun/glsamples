#ifdef _WIN32
#include<windows.h>
#endif
#include<GL/glu.h>
#include<GL/glut.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include "camera.h"
#include "bezier.h"
#define PI 3.14159265359

enum { none, freeform, circle, bezier } camera_mode;


int width, height;

float cen_x, cen_y, cen_z;
float eye_x, eye_y, eye_z;

float elevation;
float rotation;
float distance;

float _cir_d_start;
float _cir_rot_v;
float _cir_rot_start;

void close_camera()
{
	close_bezier();
	camera_mode = none; 
}

void circle_camera_loop(int m)
{
	float rad;
	float hdist;
	float orbit_angle;
	float orbit_elevation;
	float orbit_distance;

	float alpha = (float)m/100;
	--m;
	if(m < 0) m = 0;

	if(camera_mode != circle) return;
	orbit_angle = atan(eye_z / eye_x);

	if(eye_x < 0) orbit_angle += PI;

	rad = alpha * _cir_d_start + (1 - alpha) * 3000;

	orbit_angle += .01;
	rotation = orbit_angle + alpha * _cir_rot_start;
	rotation += _cir_rot_v;


	eye_x = rad * cos(orbit_angle);
	eye_z = rad * sin(orbit_angle);

	glutTimerFunc(50, circle_camera_loop, m);
	glutPostRedisplay();
}


void circle_camera(int e)
{
	if(camera_mode == circle) return;

	camera_mode = circle;
	_cir_d_start = sqrt(eye_x*eye_x + eye_z*eye_z);
	_cir_rot_start = atan(eye_z / eye_x);
	_cir_rot_v = 0;

	if(eye_x < 0) _cir_rot_start += PI;
	_cir_rot_start = rotation - _cir_rot_start;

	circle_camera_loop(100);
}

void bezier_camera_loop(int m)
{
	float dx;
	float dy;
	float dz;
	float hdist;
	point eye, cen;

	if(camera_mode != bezier) return;
	if(m >= curve[current_bezier_curve].length)
		return;

	eye = curve[current_bezier_curve].path[m];
	cen = curve[current_bezier_curve].look[m];

	dx = cen.x - eye.x; 
	dy = cen.y - eye.y; 
	dz = cen.z - eye.z;
	distance = sqrt(dx*dx + dy*dy + dz*dz);
	hdist = sqrt(dx*dx + dz*dz);
	eye_x = eye.x;
	eye_y = eye.y;
	eye_z = eye.z;
	cen_x = cen.x;
	cen_y = cen.y;
	cen_z = cen.z;

	elevation = atan(dy/hdist); 
	rotation = atan(dz/dx);
	if(dx > 0.0001) rotation += PI;


	glutTimerFunc(50, bezier_camera_loop, m+1);
	glutPostRedisplay();
}

void bezier_camera(int e)
{
	int i;
	struct bezier_curve* b = &curve[e-1];

	if((camera_mode == bezier) && (current_bezier_curve == e-1)) return;
	if((e-1) >= bez_curves);

	current_bezier_curve = e-1;
	camera_mode = bezier;
	bezier_camera_loop(0);
}

void free_camera(int e)
{
	camera_mode = freeform;
	distance = 1000;
}

void init_camera()
{
	eye_x = 0;
	eye_y = 500;
	eye_z = 2500;
	elevation = -PI/8;
	rotation = PI/2;

	load_bezier_curves();

	free_camera(0);
}

void aim_camera()
{
	float hdist = distance * cos(elevation); 

	if(camera_mode != bezier)
	{
		cen_y = eye_y + distance * sin(elevation);
		cen_x = eye_x - hdist * cos(rotation);
		cen_z = eye_z - hdist * sin(rotation);
	}

	// set perspective
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40, (float)width/height, 5, 100000);

	// set camera position/direction
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
			eye_x, eye_y, eye_z,
			cen_x, cen_y, cen_z,
			0, 1, 0
			);

	//printf("   cen (%f %f %f) distance %f\n", cen_x, cen_y, cen_z, distance);
}


/*
 *  key-presses to reposition camera and focal point
 *
 */
void freeform_move_camera(unsigned char key)
{
	float hdist = cos(elevation);

	int m = 5;
	int n = 2;

	switch(key)
	{

		// LEFT-MOVE
		case 'h':
			eye_x -= m * cos(rotation - PI/2);
			eye_z -= m * sin(rotation - PI/2);
			break;

			// RIGHT-MOVE
		case 'l':
			eye_x += m * cos(rotation - PI/2);
			eye_z += m * sin(rotation - PI/2);
			break;

			// UP-MOVE
		case 'k':
			eye_y += m;
			break;

			// DOWN-MOVE
		case 'j':
			eye_y -= m;
			break;

			// FORWARD-MOVE
		case 'n':
			eye_x -= m * cos(rotation);
			eye_z -= m * sin(rotation);
			break;

			// BACKWARD-MOVE
		case 'm':
			eye_x += m * cos(rotation);
			eye_z += m * sin(rotation);
			break;

			// IN-MOVE
		case 'i':
			eye_x -= m * hdist * cos(rotation);
			eye_z -= m * hdist * sin(rotation);
			eye_y += m * sin(elevation);
			break;

			// OUT-MOVE
		case 'o':
			eye_x += m * hdist * cos(rotation);
			eye_z += m * hdist * sin(rotation);
			eye_y -= m * sin(elevation);
			break;

			// LEFT-PAN
		case 'a':
			rotation -= n * .005;
			break;

			// RIGHT-PAN
		case 'f':
			rotation += n * .005;
			break;

			// UP-PAN
		case 's':
			elevation += n * .005;
			if(elevation >= PI/2)
				elevation = PI/2 - 0.001;
			break;

			// DOWN-PAN
		case 'd':
			elevation -= n * .005;
			if(elevation <= -PI/2)
				elevation = -PI/2 + 0.001;
			break;
	}
}


void circle_move_camera(unsigned char key)
{
	int m = 5;
	int n = 2;
	switch(key)
	{
		case 'a':
			_cir_rot_v -= 0.01;
			break;

		case 'f':
			_cir_rot_v += 0.01;
			break;

		case 'd':
			elevation -= n * .005;
			if(elevation >= PI/2)
				elevation = -PI/2 + 0.001;
			break;

		case 's':
			elevation += n * .005;
			if(elevation >= PI/2)
				elevation = PI/2 - 0.001;
			break;

		case 'j':
			eye_y -= m;
			break;

		case 'k':
			eye_y += m;
			break;

	}
}


void move_camera(unsigned char key)
{
	if(camera_mode == freeform)
		freeform_move_camera(key);
	else if(camera_mode == circle)
		circle_move_camera(key);
}

