#include <stdio.h>
#include <stdlib.h>

int main(void){
	char* test1 = "./findme . -name \"main.?\"";
	char* test2 = "./findme . -name \"*\"";
	char* test3 = "./findme . -type f -name \"code*.c\" -maxdepth 5";
	char* test4 = "./findme . -type f -name \"co?e.c\" -maxdepth 5";	
	char* test5 = "./findme . -type f -name \"[abe]xampleT*\" -maxdepth 5";

	printf("BEGIN TEST\n");	
	printf("Test 1: %s\n", test1);
	system(test1);
	printf("\nTest 2: %s\n", test2);
	system(test2);
	printf("\nTest 3: %s\n", test3);
	system(test3);
	printf("\nTest 4: %s\n", test4);
	system(test4);
	printf("\nTest 5: %s\n", test5);
	system(test5);
	printf("END TEST\n");
}
