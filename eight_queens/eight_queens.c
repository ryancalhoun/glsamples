/*
 *  animate the eight-queens problem
 */
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "solve.h"
#include "queen.h"
#include "board.h"

#ifdef _WIN32
#include<windows.h>
#define M_PI		3.14159265358979323846
#endif

#ifdef __APPLE__
#include<GLUT/glut.h>
#include<OpenGL/glu.h>
#else
#include<GL/glut.h>
#include<GL/glu.h>
#endif

// wait after move
#define WAIT 50
// wait after solution
#define LONGWAIT 30
#define MOVE_HEIGHT 40

float rot = 0;
int width, height;
int nsteps = 1;
int step = 0;
int wait = 0;
int longwait = 0;
enum { stopped, paused, waiting, moving, done, reset } state;
int resetc;


// queens - for animation only
struct
{
	float home_x, home_y, home_z;
	float last_x, last_y, last_z; 
	float next_x, next_y, next_z; 
	float move_x, move_y, move_z;
	float dist;
} queens[SOLVE_NQUEENS] = {
	{ -0.5*BOARD_SQUARE_SIZE, 0,  4.5*BOARD_SQUARE_SIZE, },
	{  4.5*BOARD_SQUARE_SIZE, 0,  0.5*BOARD_SQUARE_SIZE, },
	{ -0.5*BOARD_SQUARE_SIZE, 0, -4.5*BOARD_SQUARE_SIZE, },
	{  0.5*BOARD_SQUARE_SIZE, 0, -4.5*BOARD_SQUARE_SIZE, },
	{  4.5*BOARD_SQUARE_SIZE, 0, -0.5*BOARD_SQUARE_SIZE, },
	{ -4.5*BOARD_SQUARE_SIZE, 0, -0.5*BOARD_SQUARE_SIZE, },
	{ -4.5*BOARD_SQUARE_SIZE, 0,  0.5*BOARD_SQUARE_SIZE, },
	{  0.5*BOARD_SQUARE_SIZE, 0,  4.5*BOARD_SQUARE_SIZE, },
};

/*
 *  write text to the screen
 */
void draw_string(char* s, int x, int y)
{
	if(!s) return;
	glRasterPos2i(x, y);
	while(*s)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *s++);
}


/*
 *  draw the scene
 */
void display()
{
	int i, j;
	int light = 1;


	float pos0[] = { 200, 150, 220 };
	float pos1[] = { 150, 100, 140 };
	float pos2[] = { 50, 200, 150 };
	float intp;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40, (float)width/height, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(100, 120, 250, 0, 0, 0, 0, 1, 0);

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glRotatef(rot, 0, 1, 0);

	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, pos0);
	glLightfv(GL_LIGHT1, GL_POSITION, pos1);
	glLightfv(GL_LIGHT2, GL_POSITION, pos2);

	board_draw();

	// draw queens
	intp = (float)step/nsteps;
	for(i = 0; i < SOLVE_NQUEENS; ++i)
	{
		float p = 2*intp-1;
		float intpy; 

		int moving = 0;
		if(queens[i].dist > BOARD_SQUARE_SIZE / 2)
			moving = 1;

		if(moving)
			intpy = MOVE_HEIGHT * (1 - p*p*p*p);
		else
			intpy = 0;

		glPushMatrix();
		glTranslatef(
				(1-intp)*queens[i].last_x + intp*queens[i].next_x,
				(1-intp)*queens[i].last_y + intp*queens[i].next_y + intpy,
				(1-intp)*queens[i].last_z + intp*queens[i].next_z
				);
		if(moving)
		{
			glRotatef(90, 0, 1, 0);
			glRotatef(16*sin(2*M_PI*intp), queens[i].move_x, queens[i].move_y, queens[i].move_z);
		}
		queen_draw(i);
		glPopMatrix();
	}


	/*
	 *  print moves
	 */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_LIGHTING);
	glColor3ub(255, 255, 255);

	for(i = solve_nmessages()-1, j = 0; i >= 0; --i, ++j)
	{
		draw_string(solve_message(i), 10, 12*(j+1));
	}

	glFlush();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	width = w;
	height = h;
	glViewport(0, 0, width, height);
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	if(key == 27 || key == 'q')
	{
		exit(0);
	}

	if(key == ' ')
	{
		if(state == paused)
			state = moving;
		else if(state == moving || state == waiting)
			state = paused;
	}

}

void special(int key, int x, int y)
{
}

void get_nsteps_dir()
{
	int i;
	float maxdist = 0;
	float dx, dy, dz;
	for(i = 0; i < SOLVE_NQUEENS; ++i)
	{
		dx = queens[i].move_x = queens[i].next_x - queens[i].last_x;
		dy = queens[i].move_y = queens[i].next_y - queens[i].last_y;
		dz = queens[i].move_z = queens[i].next_z - queens[i].last_z;
		queens[i].dist = sqrt(dx*dx + dy*dy + dz*dz);
		if(queens[i].dist > maxdist)
			maxdist = queens[i].dist;
	}

	if(maxdist < BOARD_SQUARE_SIZE/2)
		nsteps = 1;
	else
		nsteps = (int)(12*log(1 + maxdist));

}

void loop(int n)
{
	static int r;
	rot += 0.02;
	if(rot > 360)
		rot = 0; 

	if(state == reset)
	{
		longwait = 0;
		r = 0;
		resetc = 0;
		state = moving; 
	}

	if(state == done)
	{
		if(longwait == LONGWAIT)
		{
			state = reset;
		}
		else
			++longwait;
	}

	else if(state == waiting)
	{
		if(wait == WAIT)
		{
			wait = 0;
			state = moving;
		}
		else ++wait;
	}
	else if(state == moving)
	{
		// start next move
		float maxdist = 0, dist;
		if(step == 0)
		{
			int i, x, z;
			if(resetc < 0)
			{
				r = solve_next_move();

				for(i = 0; i < SOLVE_NQUEENS; ++i)
				{
					solve_queen_at(i, &x, &z); 
					if(x > -1 && z > -1 && x < SOLVE_SIZE && z < SOLVE_SIZE)
					{
						queens[i].next_x = (float)(x-SOLVE_SIZE/2)*BOARD_SQUARE_SIZE + 
							BOARD_SQUARE_SIZE/2; 
						queens[i].next_z = (float)(z-SOLVE_SIZE/2)*BOARD_SQUARE_SIZE + 
							BOARD_SQUARE_SIZE/2; 
						queens[i].next_y = 0;
					}
					else
					{
						queens[i].next_x = queens[i].home_x;
						queens[i].next_y = queens[i].home_y;
						queens[i].next_z = queens[i].home_z;
					}
				}
			}
			else
			{
				queens[resetc].next_x = queens[resetc].home_x;
				queens[resetc].next_y = queens[resetc].home_y;
				queens[resetc].next_z = queens[resetc].home_z;
			}
			get_nsteps_dir();
		}
		// finished a move
		if(step == nsteps)
		{
			int i;
			step = 0;
			if(resetc < 0 || resetc == SOLVE_NQUEENS)
			{
				if(r == 0)
				{
					if(resetc == SOLVE_NQUEENS)
					{
						solve_init();
						resetc = -1;
					}
					state = waiting;
				}
				else
				{
					state = done;
				}
				for(i = 0; i < SOLVE_NQUEENS; ++i)
				{
					queens[i].last_x = queens[i].next_x;
					queens[i].last_y = queens[i].next_y;
					queens[i].last_z = queens[i].next_z;
					queens[i].move_x = queens[i].move_y = queens[i].move_z = 0;
					queens[i].dist = 0;
				}
			}
			else
			{
				queens[resetc].last_x = queens[resetc].next_x;
				queens[resetc].last_y = queens[resetc].next_y;
				queens[resetc].last_z = queens[resetc].next_z;
				queens[resetc].move_x = queens[resetc].move_y = queens[resetc].move_z = 0;
				queens[resetc].dist = 0;
				++resetc;
			}
		} 
		else ++step;
	}

	if(state)
		glutTimerFunc(20, loop, n);
	glutPostRedisplay();

}


void init()
{
	int i;
	float light0_diff[] = { 1, 1, 1, 1 };
	float light1_diff[] = { 1, 1, 1, 1 };
	float light2_diff[] = { 1, 1, 1, 1 };


	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);


	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diff);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diff);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diff);

	glShadeModel(GL_SMOOTH);

	for(i = 0; i < SOLVE_NQUEENS; ++i)
	{
		queens[i].next_x = queens[i].last_x = queens[i].home_x;
		queens[i].next_y = queens[i].last_y = queens[i].home_y;
		queens[i].next_z = queens[i].last_z = queens[i].home_z;
		queens[i].dist = 0;
	}

	state = waiting;
	resetc = -1;
}

void cleanup()
{
	state = stopped;
}

int main(int argc, char* argv[])
{
	unsigned int id[2];
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	//    glutInitWindowSize(640, 400);
	//    glutInitWindowPosition(100, 100);
	glutCreateWindow("Eight Queens Problem");

	glGenTextures(2, id);

	solve_init();
	queen_init(id[0]);
	board_init(id[1]);
	init();
	atexit(cleanup);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);

	loop(0);

	glutFullScreen();
	glutMainLoop();

	return 0;
}


