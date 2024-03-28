#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <glob.h>
#include <regex.h>

/*
https://linux.die.net/man/3/glob
One example of use is the following code, which simulates typing: ls -l *.c ../*.c

 glob_t globbuf;

 globbuf.gl_offs = 2;
 glob("*.c", GLOB_DOOFFS, NULL, &globbuf);
 glob("../*.c", GLOB_DOOFFS | GLOB_APPEND, NULL, &globbuf);
 globbuf.gl_pathv[0] = "ls";
 globbuf.gl_pathv[1] = "-l";
 execvp("ls", &globbuf.gl_pathv[0]);

 */

// gl_pathv --> list of pathnames that match the glob
// Therefore, we should only print objects that are in gl_pathv

int main(int argc, char* argv[]){
	char* name;
	if (argc == 1){
		name = "test.c";
	}
	else {
		name = argv[1];
	}

	glob_t globbuf;
	
	// While searching through directories, check if filename matches glob by calling glob after each newly constructed file path
	// Place a * before the glob to indicate that pathname doesn't matter after initial path
	// e.g. glob(*.c) would be ./*.c, glob(fi*e.c) would be ./*fi?e.c
	// Matches all C files as long as they are contained in the origin directory
	globbuf.gl_offs = 0;
 	glob("example/*.c", GLOB_DOOFFS, NULL, &globbuf);
 	//glob("example/*", GLOB_DOOFFS | GLOB_APPEND, NULL, &globbuf);

	int i = 0;
	int size = 0;	
	// Should come out as 3
	while (globbuf.gl_pathv[i] != NULL){
		size++;
		i++;
	}	

	printf("Size of globbuf: %d\n", size);
	i = 0;
	while (i < size){
		printf("Current pathname: %s\n", globbuf.gl_pathv[i]);
		i++;
	}

	/*
 	globbuf.gl_pathv[0] = "ls";
 	globbuf.gl_pathv[1] = "-l";
 	execvp("ls", &globbuf.gl_pathv[0]);
	*/
	
	return 0;
}
