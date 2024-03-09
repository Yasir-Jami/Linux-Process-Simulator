// Name: Yasir Jami (3077942)
// CMPT360 Lab 3 

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

// Will use the order:
// 0 - Regular file 
// 1 - Directory
// 2 - Symbolic Link
// 3 - Block Device
// 4 - Character Device

// Checks -file filetype given a valid argument
int checkFileType(char c){	
	switch(c){
		// Regular Files
		case 'f':
			return 0;
		// Directory
		case 'd':
			return 1;
		// Symbolic Link
		case 's':
			return 2;
		// Character Device
		case 'c':
			return 3;
		// Block Device
		case 'b':
			return 4;
		// Either invalid file type, or not one of the file types above 
		// (other types like pipe and socket are not accounted for)
		default:
			return -1;
	}
}

int fileSystemTests(char* file){
       	struct stat file_stat;
	stat(file, &file_stat);

	// Regular file
	if (S_ISREG(file_stat.st_mode)){
		printf("Regular file.\n");
		return 0;
	}
	// Directory
	else if (S_ISDIR(file_stat.st_mode)){
		printf("Directory.\n");
		return 1;
	}
	// Symbolic link
	else if (S_ISLNK(file_stat.st_mode)){
		printf("Symbolic Link.\n");
		return 2;
	}	
	// Special character
	else if (S_ISCHR(file_stat.st_mode)){
		printf("Character Special.\n");
		return 3;
	}
	// Special block
	else if (S_ISBLK(file_stat.st_mode)){
		printf("Block Special.\n");
		return 4;
	}
	
	// Realistically should never reach this point
	printf("Unknown file type.\n");
	return -1;
}

int magicNumberTests(char* file){
    FILE *fp;
    char magic_num[20]; // Holds binary data of file

    // Read binary
    if ((fp = fopen(file, "rb")) == NULL){
        printf("Cannot open file.\n");
        return -1;
    }

    // Read the first 20 bytes of the provided file
    fread(magic_num, 20, 1, fp);
    fclose(fp);

    // Find out if the first four bytes have ELF in the header
    if ((magic_num[0] == 0x7F) && (magic_num[1] == 0x45) &&
                    (magic_num[2] == 0x4c) && (magic_num[3] == 0x46)){

        // Type of ELF File can be found on the first byte of the next line on a hex dump (byte 17)
        // I guess these all evaluate to 1, 2, 3, and 4 anyway

        // Relocatable/Object file
        if (magic_num[16] == 0x01){
                return 0;
        }
        
        // Executable
        else if (magic_num[16] == 0x03){
                return 1;
        }
	
	// Shared object
        else if (magic_num[16] == 0x02){
                return 2;
        }
        
	
	// Core
        else if (magic_num[16] == 0x04){
                return 3;
        }
        return -1;
    }
 
    // If not ELF, could be executable
    // Bash script
    if (magic_num[7] == 0x62 && magic_num[8] == 0x61 &&
                        magic_num[9] == 0x73 && magic_num[10] == 0x68){
            return 4;
    }
    // Python script
    else if (magic_num[7] == 0x70 && magic_num[8] == 0x79 && magic_num[9] == 0x74 &&
                        magic_num[10] == 0x68 && magic_num[11] == 0x6f && magic_num[12] == 0x6e){
        return 5;
    }

    // If file is not ELF or bash/python executable, return -1
    return -1;
}

int asciiOrBinary(char* file){
        FILE *fp;
    	char file_contents[200]; // Holding first 200 bytes of a given file	
	int buffer_size = 200;	
	int i = 0;

    	// Read binary
    	if ((fp = fopen(file, "rb")) == NULL){
        	printf("Cannot open file.\n");
        	return -1;
	}

    	// Read the first 200 bytes of the provided file
    	fread(file_contents, buffer_size, 1, fp);
    	fclose(fp);

	// Check each byte - if there is a non-ascii byte, it is binary
	while(i < buffer_size){
		if ((file_contents[i] < 0) || (file_contents[i] > 127)){
			return 1; // Not ASCII - contains non-ASCII bytes
		}
		i++;
	}	
	return 0;
}

void printMessage(int type, int format){
	char message[50] = "";

	// If it is an ELF or executable
	if (type != -1){
		// Between 0 and 3 inclusive
		
		if (type > -1 && type < 4){	
			strcat(message, "ELF ");
		}
		
		switch(type){
                        case 0: strcat(message, "relocatable");         break;
                        case 1: strcat(message, "executable, x86-64");  break;
                        case 2: strcat(message, "shared object");       break;
                        case 3: strcat(message, "core");                break;
                        case 4: strcat(message, "bash executable");     break;
                        case 5: strcat(message, "python executable");   break;
                }
	
		printf("%s\n", message);	
	}

	// If it is not elf or executable, check its format
	else if (format != -1) {
		strcat(message, "regular file; "); 

		if (format == 0){
			strcat(message, "ASCII format");
		}

		if (format == 1){
			strcat(message, "BINARY format");
		}
		printf("%s\n", message);	
	}

	// Should realistically never reach here
	else {
		printf("Unknown file.\n");
		exit(EXIT_FAILURE);	
	}
}
