#ifdef _WIN32
#include<windows.h>
#define dlopen(p,f) (void*)LoadLibrary(p)
#define dlsym(d,f) (void*)GetProcAddress((HMODULE)(d),f)
#define dlclose(d) FreeLibrary((HMODULE)(d))
#include<w32dirent.h>
#else
#include<dlfcn.h>
#include<dirent.h>
#endif
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "buildings/building.h"

struct building* campus_buildings = 0;
int campus_building_count = 0;

int mod_filt(const struct dirent* d)
{
	return strstr(d->d_name, BUILDING_MOD_EXT);
}

void close_campus()
{
	free(campus_buildings);
}

    
void init_campus()
{
	char path[128];
	struct dirent** e;
	int n;
	int i;

	campus_building_count = n = scandir("buildings", &e, mod_filt, alphasort);
	campus_buildings = calloc(campus_building_count, sizeof(struct building));

	if(n < 0) return;
	for(i = 0; i < n; ++i)
	{
		void* h;
		sprintf(path, "buildings/%s", e[i]->d_name);
		h = dlopen(path, RTLD_LAZY);

		if(!h)
		{
			continue;
		}
		else fprintf(stdout, "loaded %s\n", path);

		campus_buildings[i].init = dlsym(h, BUILDING_INIT);
		campus_buildings[i].draw = dlsym(h, BUILDING_DRAW);

		if(campus_buildings[i].init)
			campus_buildings[i].init();

		free(e[i]);
	}
	free(e);
}


