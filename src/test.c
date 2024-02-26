#include <stdio.h>
#include "dStruct.h"
#include <math.h>

int main(void){
	double d1 = 2.0;
	double d2 = 2.0;

	if (fmod(d1, d2) == 0){
		printf("Modulus of d1\n");
	}
	else{
		printf("Not modulus of d1\n");
	}

	return 0;
}
