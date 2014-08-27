#ifndef BUILDING_H
#define BUILDING_H

#ifdef _WIN32
#include<windows.h>
typedef void (APIENTRY *cubefun)(double);
#define public __declspec(dllexport)
#else
typedef void (*cubefun)(double);
#define public
#endif

#include<GL/glu.h>
#include<GL/glut.h>


#define BUILDING_MOD_EXT ".bldg"
#define BUILDING_INIT "init"
#define BUILDING_DRAW "draw"

#define STONE 240, 240, 240
#define BRICK 160, 90, 50
#define SLATE 80, 80, 80
#define GRASS 50, 200, 50


struct building
{
	void (*init)();
	void (*draw)(int wire);
};

void norm(float verts[][3], int sides, float normal[3]);


#endif
