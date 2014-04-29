// John Beedlow - Homework #3
// catdir.cpp
// 02/24/2013
//
#include <stdio.h>
#include <stdlib.h> 
#include <dirent.h> // for directory functions
#include <sys/types.h> // for S_ISREG
#include <sys/stat.h> //  for S_ISRED
#include <unistd.h> // for chdir()


int main(int argc, char** argv) {
	
	// Varibles for holding directory and file
    struct dirent *dit;
	struct stat sta;
	DIR *dir;
	FILE *f;

	// Variables to hold file data and file size
	unsigned char *buffer;
	long fsize;
	
	// Argument error handling 
    if(argc > 2){
		printf("Error: To many arguments, please list one directory name\n");
		return 1;
	}
    else if(argc < 1){
        printf("Error: Not enough arguments, please list one directory name\n"); 
        return 1;
    }

	// Opens directory and checks to see if it is a valid entry
	dir = opendir(argv[1]);
	if(dir == NULL) {
		printf("Error: The directory %s was not able to open\n", argv[1]);
		return 1;
	}
	
	// Changes current directory to current path
	chdir(argv[1]);
	
	// Searches through directory to for files and prints them out
	// Repeat until directory is NULL
	while ((dit = readdir(dir)) != NULL) {
		stat(dit->d_name, &sta);
		if (S_ISREG(sta.st_mode)){

			// Opens file and error handles
			f = fopen(dit->d_name, "r");
			if(!f) {
				printf("%s was not able to open.\n");
				return 1;
			}

			// Finds the length of the file contents
			fseek (f, 0, SEEK_END);
			fsize = ftell(f);
			rewind(f);

			// Allocates buffer to one more then file size and error handles
			buffer = (char*)malloc(fsize+1);
			if (buffer==NULL) 
				return 1;
			
			// Reads file data into buffer and prints out the file contents
			fread(buffer, fsize, 1, f);
			int i = 0;
			while(i != fsize) {
				putchar(buffer[i]);
				++i;
			}

			// Frees buffer and closes file
			free(buffer);
			fclose(f);
			}
		}
	
	// Closes directory
	closedir(dir);
	return 0;
	
}