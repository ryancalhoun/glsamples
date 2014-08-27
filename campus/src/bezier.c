#ifdef _WIN32
#include<w32dirent.h>
#else
#include<dirent.h>
#endif
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "point.h"
#include "bezier.h"

struct bezier_curve* curve = 0;
int bez_curves = 0;
int current_bezier_curve = -1;

void close_bezier()
{
	int i;
	for(i = 0; i < bez_curves; ++i)
	{
		free(curve[i].path);
		free(curve[i].look);
	}
	free(curve);
	bez_curves = 0;
}

void bezier(point* p, float u, point a, point b, point c, point d)
{
	float B[4] = {
		(1 - u) * (1 - u) * (1 - u),
		3 * u * (1 - u) * (1 - u),
		3 * u*u * (1 - u),
		u*u*u,
	};

	int i;

	for(i = 0; i < 3; ++i)
	{
		p->v[i] = B[0]*a.v[i] + B[1]*b.v[i] + B[2]*c.v[i] + B[3]*d.v[i];
	}
}


void bezier_curve(point start, point end, point* ctrl, point* path, int n, int m)
{
	float sb_ctrl[4][3];
	point last;
	point next;
	point temp;

	int i, j, k;

	last = start;

	for(i = 0; i < n; i+= 2)
	{
		if(i == n-2)
		{
			next = end;
			k = m+1;
		}
		else
		{
			temp.v[0] = next.v[0] = (ctrl[i+1].v[0] + ctrl[i+2].v[0])/2;
			temp.v[1] = next.v[1] = (ctrl[i+1].v[1] + ctrl[i+2].v[1])/2;
			temp.v[2] = next.v[2] = (ctrl[i+1].v[2] + ctrl[i+2].v[2])/2;
			k = m;
		}

		for(j = 0; j < k; ++j)
		{
			bezier(&path[i*m/2+j], (float)j/m, last, ctrl[i], ctrl[i+1], next);
		}

		last = temp;
	} 
}


void load_bezier(char* file)
{
	point start[2];
	point end[2];
	point* ctrl[2] = {0};
	int n = 0, m = 0;
	int i;
	FILE* bez = fopen(file, "r");
	char line[256];
	char* tok;
	char* s;
	char* t;
	float* f;

	if(!bez) return;

	fgets(line, sizeof(line), bez);

	for(f = start->v, s = line; tok = strtok(s, "(,) \n"); s = 0, ++f)
		*f = atof(tok);

	while(fgets(line, sizeof(line), bez))
	{
		if(*line != '(') continue;
		++n;
		ctrl[0] = realloc(ctrl[0], n*sizeof(point));
		ctrl[1] = realloc(ctrl[1], n*sizeof(point));
		s = strtok(line, ")");
		t = strtok(0, "\n\r");
		for(f = ctrl[0][n-1].v; tok = strtok(s, "(,) "); s = 0, ++f)
			*f = atof(tok);
		for(f = ctrl[1][n-1].v; tok = strtok(t, "(,) "); t = 0, ++f)
			*f = atof(tok);
	}
	end[0] = ctrl[0][n-1];
	end[1] = ctrl[1][n-1];

	if(n > 0) --n;
	m = 100;
	++bez_curves;
	curve = realloc(curve, bez_curves*sizeof(struct bezier_curve));

	curve[bez_curves-1].path = malloc((m * (n/2) + 1)*sizeof(point));
	curve[bez_curves-1].look = malloc((m * (n/2) + 1)*sizeof(point));
	curve[bez_curves-1].length = m*(n/2)+1;

	bezier_curve(start[0], end[0], ctrl[0], curve[bez_curves-1].path, n, m);
	bezier_curve(start[1], end[1], ctrl[1], curve[bez_curves-1].look, n, m);
	free(ctrl[0]);
	free(ctrl[1]);
}

int bez_filt(const struct dirent* d)
{
	return strstr(d->d_name, ".bez");
}

void load_bezier_curves()
{
	char path[128];
	struct dirent** e;
	int n;
	int i;

	n = scandir("paths", &e, bez_filt, alphasort);
	if(n < 0) return;
	for(i = 0; i < n; ++i)
	{
		sprintf(path, "paths/%s", e[i]->d_name);
		load_bezier(path);
		printf("loaded %s\n", path);
		free(e[i]);
	}
	free(e);
}


