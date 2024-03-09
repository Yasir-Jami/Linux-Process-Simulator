// Name: Yasir Jami (3077942)
// CMPT360 Lab 3 

#ifndef FILETYPE_H
#define FILETYPE_H

// STAT FUNCTION CAN BE USED FOR THIS LAB 

/* fileSystemTests
 * Purpose: Takes a filename as argument, and returns a number indicating its file type
 * regular file=0, directory=1, characterSpecial=2, blockSpecial=3,
 * pipe=4, symbolicLink=5, socket=6
 * Parameters: char* filename: name of file to be examined
 * Return: int indicating the file's type
 */
int fileSystemTests(char* filename);

/* magicNumberTests
 * Purpose: Takes a filename (which can be assumed to be a regular file) as an argument and determines 
 * whether the file is an ELF (relocatable=0, executable=1, shared object=2, core=3) 
 * or an executable script (BASH=4, python=5).
 * Parameters: char* filename: name of file to be examined
 * Return: int indicating whether it is an ELF or executable, and what kind it is
 */
int magicNumberTests(char* filename);

/* asciiOrBinary
 * Purpose: Takes a filename and determines if the file is in ASCII or Binary format
 * Parameters: char* filename: name of file to be examined 
 * Return: int indicating whether the file contents are in ASCII or BINARY
 */
int asciiOrBinary(char* filename);

/* Additional Notes:
 * Filenames can not be used to determine the type (don't look at extension to determine type) 
 * Can look at first four bytes of a file to determine if it is an ELF file
 */

/* printMessage
 * Purpose: Changes the message to include the type of file or the format (ascii or binary)
 * Parameters: type: determines if file is of type ELF or executable, 
 * 	       format: if it is not ELF or executable, determines if file is ascii or binary
 * Return: the message after determining the type of file or its format
 */
void printMessage(int type, int format); 

#endif
