/*
 *  draw the chessboard
 *
 */
#include<stdlib.h>
#include "board.h"
#include "solve.h"
#include "queen.h"

#ifdef _WIN32
#include<windows.h>
#endif

#ifdef __APPLE__
#include<OpenGL/gl.h>
#include<OpenGL/glu.h>
#else
#include<GL/gl.h>
#include<GL/glu.h>
#endif

#define TEX_S 64

static unsigned int tex_id;
static unsigned char tex[TEX_S][TEX_S][3];


/*
 *  create a texture for 1/4 of the chessboard
 */
static void fill_tex(unsigned char tex[TEX_S][TEX_S][3])
{
	int i, j;

	// maps for light squares
	unsigned char cmap[15] = { 
		220, 230, 240, 245, 245, 
		250, 250, 250, 252, 252,
		252, 252, 254, 255, 255,
	};

	unsigned char emap[15] = { 
		130, 140, 144, 144, 146,
		150, 150, 152, 156, 160,
		170, 172, 176, 178, 180,
	};

	unsigned char bmap[15] = { 
		180, 180, 181, 182, 183,
		185, 185, 188, 190, 192,
		196, 198, 200, 201, 202,
	};

	for(i = 0; i < TEX_S; ++i)
	{
		for(j = 0; j < TEX_S; ++j)
		{
			unsigned char c;
			//            if(i > 1 && i < TEX_S-2 && j > 1 && j < TEX_S-2)
			//                c = cmap[rand()%15];
			if(i > 0 && i < TEX_S-1 && j > 0 && j < TEX_S-1)
				c = cmap[rand()%15];
			else
				c = bmap[rand()%15];
			tex[i][j][0] = c;
			tex[i][j][1] = c;
			tex[i][j][2] = c;
		}
	}
}


/*
 *  initialize texture
 */
void board_init(int id)
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
			0, GL_RGB, TEX_S, TEX_S, 
			0, GL_RGB, GL_UNSIGNED_BYTE, tex);

}


/*
 *  draw using the texture, repeated 4 times
 */
void board_draw()
{
	int i, j, light = 1;

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, tex_id);

	glBegin(GL_QUADS);
	for(i = 0; i < BOARD_SIZE; ++i)
	{
		for(j = 0; j < BOARD_SIZE; ++j)
		{
			if(light)
				glColor3ub(220, 170, 90);
			else
				glColor3ub(70, 30, 20);
			glNormal3f(0, 1, 0);
			glTexCoord2f(0, 0);
			glVertex3f(BOARD_SQUARE_SIZE*(i-BOARD_SIZE/2),0,BOARD_SQUARE_SIZE*(j-BOARD_SIZE/2));
			glTexCoord2f(0, 1);
			glVertex3f(BOARD_SQUARE_SIZE*(i-BOARD_SIZE/2),0,BOARD_SQUARE_SIZE*(j+1-BOARD_SIZE/2));
			glTexCoord2f(1, 1);
			glVertex3f(BOARD_SQUARE_SIZE*(i+1-BOARD_SIZE/2),0,BOARD_SQUARE_SIZE*(j+1-BOARD_SIZE/2));
			glTexCoord2f(1, 0);
			glVertex3f(BOARD_SQUARE_SIZE*(i+1-BOARD_SIZE/2),0,BOARD_SQUARE_SIZE*(j-BOARD_SIZE/2));

			light = !light;
		}
		light = !light;
	}


	glEnd();
	glFlush();
	glDisable(GL_TEXTURE_2D);

}

