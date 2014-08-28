// OS stuff, OpenGL headers
#ifdef _WIN32
#include<windows.h>
#endif

#ifdef __APPLE__
#include<OpenGL/glut.h>
#include<OpenGL/glu.h>
#include<OpenGL/gl.h>
#else
#include<GL/glut.h>
#include<GL/glu.h>
#include<GL/gl.h>
#endif

#include<math.h>

// windows does not define PI
#ifndef M_PI
#define M_PI 3.14159
#endif

// regular headers
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

// solar system headers
#include "sun.h"
#include "planet.h"
#include "moon.h"


// global states
static int go;
static float speed;
static int width, height;
static int orbit;
static float dist, elev, rot;

static struct sun s;

static GLUquadric* q;

/*
 *
 */
void display()
{
	float pos[] = { 0, 0, 0, 1 };

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40, (float)width/height, 10, 10000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, dist, 0, 0, 0, 0, 1, 0);

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);

	glColor3ub(1, 0, 0);
	glutSolidSphere(100, 20, 20);

	glPushMatrix();
	glRotatef(elev, 1, 0, 0);
	glRotatef(rot, 0, 1, 0);
	drawSun(&s, q, orbit);
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

/*
 *
 */
void reshape(int w, int h)
{
	width = w;
	height = h;

	glViewport(0, 0, width, height);

	glutPostRedisplay();
}

/*
 *
 */
void loop(int n)
{
	int i, j; 
	if(!go)
		return;

	for(i = 0; i < s.nplanets; ++i)
	{
		s.planets[i].a += speed * 50 / s.planets[i].p;
		if(s.planets[i].a > 360.0)
			s.planets[i].a -= 360.0;
		for(j = 0; j < s.planets[i].nmoons; ++j)
		{
			s.planets[i].moons[j].a += speed * 50 / s.planets[i].moons[j].p;
			if(s.planets[i].moons[j].a > 360.0)
				s.planets[i].moons[j].a -= 360.0; 
		}
	}

	glutTimerFunc(50, loop, n);
	glutPostRedisplay();
}

/*
 *
 */
void keyboard(unsigned char k, int x, int y)
{
	if(k == 'q')
		exit(0);

	if(k == 'j' && elev > -85)
		elev -= 2;
	if(k == 'k' && elev < 85)
		elev += 2;

	if(k == 'i' && dist > 200)
		dist -= 5;
	if(k == 'o')
		dist += 5;

	if(k == 'h')
		rot += 2;
	if(k == 'l')
		rot -= 2;

	if(k == 's')
		orbit = !orbit;

	if(isdigit(k))
	{
		char s[2] = { k };
		int sp = atoi(s);
		if(sp == 0) sp = 10;
		speed = pow(2, sp);
	}
}

/*
 *
 */
void init_ss(char* file)
{
	struct planet p = { 0 };
	struct moon m = { 0 };

	FILE* f = fopen(file, "r");
	char line[80];
	int i = -1;
	int j = -1;

	s.nplanets = 0;
	s.planets = 0;

	srand(time(0));

	while(fgets(line, sizeof(line), f))
	{
		char* k;
		char* v;

		strtok(line, "\n\r");
		if(!strstr(line, "="))
			continue;

		// sun
		if(strstr(line, "sun:"))
		{
			k = strtok(line, " =");
			v = strtok(0, " =");
			if(k && v)
				setSunAttr(&s, k, v);
		}

		// moon
		else if(*line == ' ')
		{
			k = strtok(line, " =");
			v = strtok(0, " =");
			if(strstr(line, "moon")){
				s.planets[i].nmoons = (++j)+1;
				s.planets[i].moons = realloc(s.planets[i].moons, 
						s.planets[i].nmoons*sizeof(struct moon));
				s.planets[i].moons[j] = m;
				s.planets[i].moons[j].a = rand()%360;

				continue;
			}
			if(k && v)
				setMoonAttr(&s.planets[i].moons[j], k, v);
		}
		// planet
		else 
		{
			k = strtok(line, " =");
			v = strtok(0, " =");
			if(strstr(line, "planet"))
			{
				s.nplanets = (++i)+1;
				s.planets = realloc(s.planets, s.nplanets*sizeof(struct planet));
				s.planets[i] = p;
				s.planets[i].a = rand()%360;
				j = -1;
				continue;
			}
			if(k && v)
				setPlanetAttr(&s.planets[i], k, v);
		}
	}

	fclose(f);
}

/*
 *
 */
void init()
{
	go = 1;
	speed = 5;

	dist = 1000;
	elev = 10;
	rot  = 45;
	orbit = 0;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	q = gluNewQuadric();
	gluQuadricDrawStyle(q, GLU_FILL);
	gluQuadricOrientation(q, GLU_OUTSIDE);
	gluQuadricNormals(q, GLU_SMOOTH);
}

/*
 *
 */
void cleanup()
{
	int i;
	go = 0;

	for(i = 0; i < s.nplanets; ++i)
	{
		if(s.planets[i].nmoons)
			free(s.planets[i].moons);
		s.planets[i].nmoons = 0;
	}
	free(s.planets);
	s.nplanets = 0;

	gluDeleteQuadric(q);
}

/*
 *
 */
int main(int argc, char* argv[])
{
	if(argc == 1)
	{
		fprintf(stderr, "use: %s solarsystem_def\n", argv[0]);
		exit(0);
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
	glutCreateWindow("Solar System");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	init();
	init_ss(argv[1]);
	loop(0);
	atexit(cleanup);

	glutFullScreen();
	glutMainLoop();

	return 0;
}


