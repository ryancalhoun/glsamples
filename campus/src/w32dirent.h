#ifdef _WIN32

#ifndef DIRENT_INCLUDED
#define DIRENT_INCLUDED
#include <errno.h>
#include <io.h> /* _findfirst and _findnext set errno iff they return -1 */
#include <stdlib.h>
#include <string.h>

/*

    Declaration of POSIX directory browsing functions and types for Win32.

    Author:  Kevlin Henney (kevlin@acm.org, kevlin@curbralan.com)
    History: Created March 1997. Updated June 2003.
    Rights:  See end of file.
    
*/

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct DIR DIR;

struct dirent
{
	char *d_name;
};

struct DIR
{
	long                handle; /* -1 for failed rewind */
	struct _finddata_t  info;
	struct dirent       result; /* d_name null iff first time */
	char                *name;  /* null-terminated char string */
};

DIR           *opendir(const char *name);
int           closedir(DIR *d);
struct dirent *readdir(DIR *d);
void          rewinddir(DIR *d);
int           alphasort( struct dirent **a, struct dirent **b);
int           scandir(const char* dir, struct dirent*** namelist, 
int           (*select)(struct dirent*), 
int           (*cmp)(const void* a, const void* b));

/*

    Copyright Kevlin Henney, 1997, 2003. All rights reserved.

    Permission to use, copy, modify, and distribute this software and its
    documentation for any purpose is hereby granted without fee, provided
    that this copyright and permissions notice appear in all copies and
    derivatives.
    
    This software is supplied "as is" without express or implied warranty.

    But that said, if there are any problems please get in touch.

*/



#ifdef __cplusplus
}
#endif
#endif
#endif
