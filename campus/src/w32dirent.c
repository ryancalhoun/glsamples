#ifdef _WIN32

#include<w32dirent.h>

/*

    Copyright Kevlin Henney, 1997, 2003. All rights reserved.

    Permission to use, copy, modify, and distribute this software and its
    documentation for any purpose is hereby granted without fee, provided
    that this copyright and permissions notice appear in all copies and
    derivatives.
    
    This software is supplied "as is" without express or implied warranty.

    But that said, if there are any problems please get in touch.

*/



int alphasort( struct dirent **a, struct dirent **b)
{
	return strcmp ((*a)->d_name, (*b)->d_name);
}

extern int errno;

int scandir (dir, namelist, select, cmp)
     const char *dir;
     struct dirent ***namelist;
     int (*select)(struct dirent *);
     int (*cmp)(const void *, const void *);
{
	DIR *dp = opendir (dir);
	struct dirent **v = NULL;
	size_t vsize = 0, i;
	struct dirent *d;
	int save;

	if (dp == NULL)
		return -1;

	save=errno=0;

	i = 0;
	while ((d = readdir (dp)) != NULL)
		if (select == NULL || (*select) (d))
		{

			if (i == vsize)
			{
				struct dirent **new;
				if (vsize == 0)
					vsize = 10;
				else
					vsize *= 2;
				new = (struct dirent **) realloc (v, vsize * sizeof (*v));
				if (new == NULL)
				{
lose:
					errno=ENOMEM;

					break;
				}
				v = new;
			}

			v[i] = (struct dirent *) malloc (sizeof(struct dirent));
			v[i]->d_name = (char *)malloc(strlen( d->d_name ) + 1 );
			if (v[i] == NULL)
				goto lose;

			strcpy( v[i]->d_name, d->d_name );
			i++;
		}

	if( errno == ENOENT ) errno = 0;
	if (errno != 0)
	{
		save = errno;
		(void) closedir (dp);
		while (i > 0)
			free (v[--i]);
		free (v);
		errno=save;
		return -1;
	}

	(void) closedir (dp);
	errno=save;

	/* Sort the list if we have a comparison function to sort with.  */
	if (cmp != NULL)
		qsort (v, i, sizeof (*v), cmp);
	*namelist = v;
	return i;
}




DIR *opendir(const char *name)
{
	DIR *dir = 0;

	if(name && name[0])
	{
		size_t base_length = strlen(name);
		const char *all = /* search pattern must end with suitable wildcard */
			strchr("/\\", name[base_length - 1]) ? "*" : "/*";


		if((dir = (DIR *) malloc(sizeof *dir)) != 0 &&
				(dir->name = (char *) malloc(base_length + strlen(all) + 1)) != 0)
		{
			strcat(strcpy(dir->name, name), all);

			if((dir->handle = (long) _findfirst(dir->name, &dir->info)) != -1)
			{
				dir->result.d_name = 0;
			}
			else /* rollback */
			{
				free(dir->name);
				free(dir);
				dir = 0;
			}
		}
		else /* rollback */
		{
			free(dir);
			dir   = 0;
			errno = ENOMEM;
		}
	}
	else
	{
		errno = EINVAL;
	}
	return dir;
}

int closedir(DIR *dir)
{
	int result = -1;

	if(dir)
	{
		if(dir->handle != -1)
		{
			result = _findclose(dir->handle);
		}

		free(dir->name);
		free(dir);
	}

	if(result == -1) /* map all errors to EBADF */
	{
		errno = EBADF;
	}

	return result;
}

struct dirent *readdir(DIR *dir)
{
	struct dirent *result = 0;

	if(dir && dir->handle != -1)
	{
		if(!dir->result.d_name || _findnext(dir->handle, &dir->info) != -1)
		{
			result         = &dir->result;
			result->d_name = dir->info.name;
		}
	}
	else
	{
		errno = EBADF;
	}

	return result;
}

void rewinddir(DIR *dir)
{
	if(dir && dir->handle != -1)
	{
		_findclose(dir->handle);
		dir->handle = (long) _findfirst(dir->name, &dir->info);
		dir->result.d_name = 0;
	}
	else
	{
		errno = EBADF;
	}
}

#endif
