/**
 * Copyright (C) 2001 Vasili Gavrilov <vgavrilov AAAATTTTT users.sourceforge.net>
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _COMMON_H
#define _COMMON_H
#include <getopt.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include <sys/stat.h>
/* #include <sys/uio.h> */  /* we do not use locks here */
#include <sys/types.h>
#include <sys/file.h>


#define BOOL	int
#define TRUE	1
#define FALSE	0

extern int debug;
extern int trace;

void rtrim(char * string, char trim);
void ltrim(char * string, char trim);
char *strdup(const char *str); /* duplicate string - when not 2001 POSIX (XSI) */
unsigned int mysnprintf(char *buf, size_t size, const char *fmt, ...); /* if snprintf is not availbale */


/**********************
 * Logging stuff below
 **********************/
int LOG(char* fmt, ...);

/* variadic macros working only with C99 compilers: */
#define PRINT(mesg, ...) fprintf(stdout, mesg, __VA_ARGS__)

#ifdef DEBUG
#define DPRINT(mesg, ...) fprintf(stdout, mesg, __VA_ARGS__)
#else
#define DPRINT(mesg, ...)
#endif

#define OUT_OF_MEM() { \
			fprintf(stderr, "Out of memory: %s:%d", __FILE__, __LINE__); \
			exit(-1); \
		}

#define FATAL(X){ \
		fprintf(stderr, X); \
		exit(-1); \
	}

#endif /* __COMMON_H__ */
