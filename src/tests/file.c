#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argsv[]){
	FILE *fp = NULL;	
	char fullfname[50] = "";
	char fname[] = "./logfile";
	char algorithm[12] = "ALGOR_RR";
	char date[16]  = __DATE__;	
	int i = 0;

	while (date[i] != '\0'){		
		if (date[i] == ' '){
			date[i] = '-';
		}
		i++;
	}	
	
	sprintf(fullfname, "%s-%s-%s", fname, date, algorithm);

	fp = fopen(fullfname, "a");
	fprintf(fp, "%s %s\n", argsv[1], argsv[2]);
	
	fclose(fp);
}
