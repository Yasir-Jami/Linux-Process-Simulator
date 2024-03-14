#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>

int main(void){

	int fs;
	struct stat buf;

	char filename[]="wcode04.c";

	if( (fs=stat(filename,&buf))<0  ){
		printf("stat did not work!\n");
		exit(EXIT_FAILURE);
	}

	printf("UID: %i\n",buf.st_uid);
	printf("GID: %i\n",buf.st_gid);
	printf("MOD: %i\n",buf.st_mode);
	printf("SIZE:%li\n",buf.st_size);

	if(S_ISREG(buf.st_mode)){
		printf("Is a regular file\n");
	}

}
