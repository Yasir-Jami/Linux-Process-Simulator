#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<dirent.h>

int main(void){

int fs;
struct stat buf;
DIR* d;
struct dirent* data;

if( (fs=stat("old",&buf)) < 0  ){
	printf("Cannot find file\n");
	exit(EXIT_FAILURE);
}

if( !S_ISDIR(buf.st_mode) ){
	printf("Not a directory\n");
	exit(EXIT_FAILURE);
}

if( (d=opendir("old"))==NULL){
	printf("Could not open directory\n");
	exit(EXIT_FAILURE);
}

while( (data = readdir(d))!=NULL  ){
	printf("%s\n",data->d_name);
}

closedir(d);


}
