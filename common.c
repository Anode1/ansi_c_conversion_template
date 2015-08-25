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

#include "common.h"

int debug = 0; /* default is 0 = no debug */
int trace = 0; /* extremely verbose logging (into the log file) - veeeery slow */

void rtrim(char * string, char trim){
	int i;
	for(i = strlen(string)-1; (i >= 0) && (strchr (string + i, trim)!=NULL); i--)
		string[i] = '\0';
}

/* not efficient - please rewrite me! */
void ltrim(char * string, char trim){
	while((*string != '\0') && (strchr (string, trim)!=NULL))
		memmove(string, string+1, strlen(string));
}


/* Safe version of sprintf */
unsigned int mysnprintf(char *buf, size_t size, const char *fmt, ...){

	 unsigned int n;
	 va_list  ap;
	 va_start(ap, fmt);
	 vsprintf(buf, fmt, ap);
	 n = strlen(buf);
	 va_end(ap);
	 if (n >= size){
		 printf("snprintf: '%s' overflowed array", fmt);
	 }
	 return(n);
}

/* duplicate string - when not 2001 POSIX (XSI) */
char *strdup(const char *str){

	size_t len;
	char *copy;

	if(!str) /* NULL passed? return NULL as well */
		return NULL;

	len = strlen(str) + 1;
	copy = (char*)malloc(len);
	if(copy == NULL)
		OUT_OF_MEM();

	strcpy(copy, str);

	return copy;
}

/* print debug message */
int LOG(char *fmt, ...){

	char* logfile = ".log";
	int fd;
	char buf[1024];
	va_list ap;

	errno=0;
	fd = open(logfile, O_WRONLY|O_APPEND|O_CREAT, 0664);
	if(fd<0){
		fprintf(stderr, "Can't open log file %s: %s\n", logfile, strerror(errno));
		return -1;
	}

	strcpy(buf, "[DEBUG] ");
	write(fd, buf, strlen(buf));

	va_start(ap, fmt);
    vsprintf(buf, fmt, ap);
	va_end(ap);

    write(fd, buf, strlen(buf));
    write(fd, "\n", 1);

	close(fd);

	return 0;
}

