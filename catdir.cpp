// John Beedlow - Homework #3
// catdir.cpp
// 02/24/2013
//
#include <stdio.h>
#include <string>
#include <dirent.h> // for directory functions
#include <sys/types.h> // for S_ISREG
#include <sys/stat.h> //  for S_ISRED
#include <unistd.h> // for chdir()

int main(int argc, char** argv) {
	
	// Varibles for holding directory
    struct dirent *dit;
	struct stat sta;
	std::string filename;
	DIR *dir;

	// Opens directory
	dir = opendir(argv[1]);

	// Error Handling 
    if(argc > 1){
		if(dir == NULL) {
			printf ("Error: The directory %s was not able to open\n", argv[1]);
			return 1;
		}
	}
    else {
        printf("Error: Not enough arguments, please list one directory name\n"); 
        return 1;
    }

	chdir((char *)dir);

	// Searches through directory to for files and prints them out
	// Reapeat untill directory is NULL
	while ((dit = readdir(dir)) != NULL) {
		stat(dit->d_name, &sta);
		if (S_ISREG(sta.st_mode))
			printf ("%s\n", dit->d_name);
	}
	
	// Closes directory
	closedir(dir);
    return 0;
}

