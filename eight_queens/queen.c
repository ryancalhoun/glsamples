/*
 *  draw a queen, following a defined surface outline
 *
 */
#include "queen.h"
#include<math.h>

#ifdef _WIN32
#include<windows.h>
#define M_PI		3.14159265358979323846
#define M_PI_4		0.78539816339744830962
#define M_SQRT2		1.41421356237309504880
#endif

#ifdef __APPLE__
#include<OpenGL/gl.h>
#else
#include<GL/gl.h>
#include<GL/glut.h>
#endif

#define TEX_S 64
static unsigned int tex_id;
static unsigned char tex[TEX_S][2][3];

// the surface outline
#define NSURF 27
struct {
	float r;
	float y;
} queen_surf[NSURF] = {
	{ 90,  0},
	{100,  2},
	{ 95,  7},
	{ 88, 10},
	{ 92, 14},
	{ 91, 15},
	{ 78, 17},
	{ 75, 19},
	{ 70, 20},
	{ 50, 70},
	{ 70, 70},
	{ 70, 72},
	{ 55, 74},
	{ 54, 76},
	{ 48, 78},
	{ 48, 80},
	{ 52, 82},
	{ 47, 84},
	{ 45, 90},
	{ 64, 92},
	{ 63, 94},
	{ 46, 94},
	{ 44, 92},
	{ 22, 92},
	{ 20, 96},
	{ 18, 98},
	{  0,100},
};


static void fill_tex(unsigned char tex[TEX_S][2][3])
{
	int i;

	// maps for light squares
	unsigned char map[15] = { 
		200, 225, 226, 227, 228, 
		230, 232, 234, 236, 238,
		240, 246, 254, 255, 255,
	};

	for(i = 0; i < TEX_S; ++i)
	{
		unsigned char c = map[rand()%15];
		tex[i][0][0] = tex[i][1][0] = c;
		tex[i][0][1] = tex[i][1][1] = c;
		tex[i][0][2] = tex[i][1][2] = c;
	}
}

/*
 *
 */
void queen_init(int id)
{
	int i, j;

	tex_id = id;
	fill_tex(tex);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	//glGenTextures(1, &tex_id);

	glBindTexture(GL_TEXTURE_2D, tex_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 
			0, GL_RGB, 2, TEX_S,
			0, GL_RGB, GL_UNSIGNED_BYTE, tex);

}


/*
 *  draw polygons for the queen surface 
 */
void queen_draw(int q)
{
	int i, j;

	if(q % 2)
		glColor3ub(220, 130, 80);
	else
		glColor3ub(50, 20, 10);

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, tex_id);


	glBegin(GL_QUADS);

	// angle
	for(j = 0; j < 50; ++j)
	{
		float a0 = 2*M_PI*(float)j/50;
		float a1 = 2*M_PI*(float)(j+1)/50;

		// surface
		for(i = 0; i < NSURF-1; ++i)
		{
			float r0 = QUEEN_R*queen_surf[i].r/100;
			float r1 = QUEEN_R*queen_surf[i+1].r/100;

			float y0 = QUEEN_HEIGHT*queen_surf[i].y/100;
			float y1 = QUEEN_HEIGHT*queen_surf[i+1].y/100;

			float x0_0 = r0*cos(a0);
			float x0_1 = r0*cos(a1);
			float x1_0 = r1*cos(a0);
			float x1_1 = r1*cos(a1);
			float xp_0 = r0*M_SQRT2*cos(a0 + M_PI_4);
			float xp_1 = r0*M_SQRT2*cos(a1 + M_PI_4);

			float z0_0 = r0*sin(a0);
			float z0_1 = r0*sin(a1);
			float z1_0 = r1*sin(a0);
			float z1_1 = r1*sin(a1);
			float zp_0 = r0*M_SQRT2*sin(a0 + M_PI_4);
			float zp_1 = r0*M_SQRT2*sin(a1 + M_PI_4);

			float ax0 = x0_0 - xp_0;
			float ay0 = y0   - y0;
			float az0 = z0_0 - zp_0;

			float ax1 = x0_1 - xp_1; 
			float ay1 = y0   - y0;
			float az1 = z0_1 - zp_1;

			float bx0 = x1_0 - x0_0;
			float by0 = y1   - y0; 
			float bz0 = z1_0 - z0_0;

			float bx1 = x1_1 - x0_1;
			float by1 = y1   - y0; 
			float bz1 = z1_1 - z0_1;

			float nx0 = ay0*bz0 - by0*az0;
			float ny0 = az0*bx0 - bz0*ax0;
			float nz0 = ax0*by0 - bx0*ay0; 

			float nx1 = ay1*bz1 - by1*az1;
			float ny1 = az1*bx1 - bz1*ax1;
			float nz1 = ax1*by1 - bx1*ay1; 

			// vertical size 1
			glNormal3f(nx0, ny0, nz0);
			glTexCoord2f(0, y0/QUEEN_HEIGHT);
			glVertex3f(x1_0, y1, z1_0);
			glTexCoord2f(0, y1/QUEEN_HEIGHT);
			glVertex3f(x0_0, y0, z0_0);

			// vertical size 2
			glNormal3f(nx1, ny1, nz1);
			glTexCoord2f(1, y1/QUEEN_HEIGHT);
			glVertex3f(x0_1, y0, z0_1);
			glTexCoord2f(1, y0/QUEEN_HEIGHT);
			glVertex3f(x1_1, y1, z1_1);
		}
	}

	glEnd();
	glFlush();
	glDisable(GL_TEXTURE_2D);
}




