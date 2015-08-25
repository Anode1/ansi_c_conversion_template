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

#include "main.h"

static char *filename;
static char *mapfile; 
static char *outfilename;

struct hash* params;


#ifndef UNIT_TEST

/* ----------------------------------------------------------- */
int main(int argc, char **argv){

	int exit_code;	

	if((exit_code = parse_params(argc, argv)))
		return exit_code; /* not 0 - if something wrong or help */

	if((exit_code = load_mapping())){
		fprintf(stderr, "Can't load mappings %s\n", strerror(errno));
		return exit_code;
	}

	if((exit_code = process())){
		fprintf(stderr, "Can't process\n");
		return exit_code;
	}

	return exit_code;
}


/* 
 * Prints help message if something wrong with arguments
 */
static void wrong_args(){
	fprintf(stderr, "Wrong arguments. Try 'is -h' for reference.\n");
}


static int parse_params(int argc, char **argv){

	int c;
	while ((c = getopt(argc, argv, "i:m:hdt")) != -1){
		switch (c){
			case 'i':
				filename=optarg;
				break;
			case 'm':
				mapfile=optarg;
				break;			
			case 'h':
				help();
				return 1; /* help - no need in continuing: exit */
			case 'd':
				debug = 1;
				break;
			case 't':
				trace = 1;
				break;				
			default :
				wrong_args();
				return -1; /* wrong args -> exit */
		}/* switch */
	}/* while (all args) */

	int i;
	for(i=0 ; optind < argc; ++optind){
		/* if(debug)printf("argv[%d]='%s'\n", optind, argv[optind]); */
		if(i==0)
			filename=argv[optind];
		if(i==1)
			mapfile=argv[optind];
		i++;
	}
	
	if(!filename){
		help();
		return -1;	 
		/* filename="TestFile.txt"; */ 
	}
	
	if(!mapfile){
		mapfile="snips";
	}
	
	return 0;
}


/* process file */
static int process(){


	return 0;
}


static int load_mapping(){


	return 0;
}


/* 
 * Prints detailed help screen
 */
static void help(){
	
	fprintf(stdout, "\n\
ped2raw conversion utility \n\
Version 1.0\n\
\n\
SYNOPSIS\n\
	ped2raw <input_file>\n\
	ped2raw <input_file> <map_file>\n\
	(for more examples see below)\n\
OPTIONS:\n\
    -h         Print this help screen\n\
    -d         Debug\n\
	\n\
EXAMPLES:\n\
   ped2raw TestFile.ped\n\
\n\
   ped2raw \"Testing 0607 Data.ped\" snips_map\n");
                   
}
	
#endif 
