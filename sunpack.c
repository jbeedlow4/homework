/**************
 * ***************************************
 * sunpack - Simple Unpack
 *
 * This program unpacks files created
 * with spack (simple pack).
 *
 * Author: John Beedlow <jbeedlo2@kent.edu>
 * Date: 3/17/2014
 * Version: 1.1
 *
 * Original Author: Doug Stanley <dmstanle@kent.edu>
 ******************************************************/

#include "spack.h"
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <getopt.h>
#include <stdint.h> 

// Function declaration that I wrote
void list(char *);
void extractSingle(char *, char *, char *);
void unpackAll(char *);

int main(int argc, char **argv){

    struct sunpack_args flags;

    /**********************************************
     * This function parses all the command line
     * arguments for you and fills in the struct.
     * It also handles any errors associated with
     * the command line, so you can assume if it
     * returns, then you can trust the values in
     * the struct as being correct.
     **********************************************/
    parse_args(argc, argv, &flags);

    if( flags.list ){
		printf("Listing files in %s.\n", flags.packfile);
		// Variables that hold file information
	uint64_t fileSize;
	short fileNameLen[1];

	// Opens and tests packfile
	FILE *leFile;
	leFile = fopen("example.spack", "r");
	if (leFile == NULL) {
		perror("File did not open\n");
		exit(EXIT_FAILURE);
	}

	// Sets file pointer to size of filename
	fseek(leFile, 4, SEEK_SET);
	printf("fgdsaga");
	// Loops untill at end of file
	int p = 0;
	while((p = fgetc(leFile)) != EOF) {
		ungetc(p, leFile);
		// Reads in the size of file name
		fread(fileNameLen, sizeof(short), 1, leFile);

		// Reads in the file name
		char fileName[fileNameLen[0] + 1]; 
		fread(fileName, sizeof(char), fileNameLen[0], leFile);
		fileName[fileNameLen[0]] = '\0';

		// Reads in the length of file size
		fread(&fileSize, sizeof(uint64_t), 1, leFile);
			
		// Prints out file name and file size
		printf("%-20lld\t%s\n", fileSize, fileName); //print_file_record(fileName, fileSize);

		// Jumps file pointer to next file in pack file
		fseek(leFile, fileSize, SEEK_CUR);	
	}	
}

	else if(flags.extract && flags.extract_single) {
		printf("Listing %s in %s.\n", flags.extract, flags.packfile);
		extractSingle(flags.dest, flags.file_name, flags.packfile);

	}
}

/**********************************************
 * usage
 *
 * Takes argv from main, and prints out
 * command line usage for the program
 * (i.e. expected command arguments )
 * This function terminates the program.
 * It's meant to be run when the user supplied
 * wrong command line arguments, and therefore
 * the program has to stop.
 ***********************************************/
void usage(char **argv){
    printf("Usage: \n");
    printf("%s -h \n", argv[0]);
    printf("or\n");
    printf("%s [ -l | -x DIR ] [ -f FILE ] PACK_FILE\n",argv[0]);
    printf("Where:\n");
    printf("%-10s - Print this help message and exit.\n", "-h");
    printf("%-10s - Print filename and size of all files in PACK_FILE.\n", "-l");
    printf("%-10s - Extract files into directory DIR.\n", "-x DIR");
    printf("%-10s - Extract only file named FILE.\n", "-f FILE");
    printf("%-10s - The name of the packed file to operate on (required!).\n","PACK_FILE");
    printf("\nNote: -l and -x are mutually exclusive. Only one can be specified at a time.\n");

    exit(1);
}

/***************************************************
 * parse_args
 * 
 * This function takes the args from the command
 * line and parses them using getopt, filling in
 * in the sunpack_args struct with the options
 * the user passed in.
 *
 * No return value. Function just returns on succes,
 * terminates the program with usage info on error.
 ****************************************************/
void parse_args(int argc, char **argv, struct sunpack_args * flags){
    int c = 0;

    //make sure there ARE arguments
    if( argc < 2 ) usage(argv);

    //Initialize struct
    flags->list = 0;
    flags->extract = 0;
    flags->extract_single = 0;
    flags->dest = NULL;
    flags->file_name = NULL;


    while( ( c = getopt( argc, argv, "hx:f:l" ) ) != -1 ){
        fprintf(stderr,"%c\n",c);
        switch(c){
            case 'h':
                fprintf(stderr,"Asked for help!\n");
                usage(argv);
                break;
            case 'l':
                flags->list++;
                break;
            case 'x':
                flags->extract++;
                flags->dest = optarg;
                fprintf(stderr,"DEST: %s\n",optarg);
                break;
            case 'f':
                flags->file_name = optarg;
                flags->extract_single++;
                break;
            default:
                //unknown option
                fprintf(stderr,"Uknown option specified!\n");
                usage(argv);
        }
    }

    if( flags->list > 0 && flags->extract > 0 ){
        //both flags shouldn't be set, so print help
        fprintf(stderr,"You can't specify -l and -x at the same time!\n");
        usage(argv);
    } else if( flags->extract_single > 0 && flags->extract < 1 ){
        fprintf(stderr,"If you specify -f, you have to also specify -x!\n");
        usage(argv);
    }

    if( optind < argc ){
        flags->packfile = argv[optind];
    }else{
        fprintf(stderr,"No pack file specified!\n");
        usage(argv);
    }
}

/********************************************
 * This function prints out a single file
 * record from a pack file.
 *
 * Having everyone use the same function,
 * ensures that everyone's code will have
 * a uniform and testable output.
 *******************************************/

/*void print_file_record(char *fname, uint64_t fsize){
    printf("%-20lld\t%s\n", fsize, fname);
}*/

///////////////////////////////////////////////////////
//////////// Functions that I wrote ///////////////////
/////////////////////////////////////////////////////// 
void list(char *path) {

	
}	

void extractSingle(char* destPath, char* file, char* path) {
	printf("Poopy");
	// Variables that hold file information
	uint64_t fileSize;
	short fileNameLen[1];

	// Opens and tests packfile
	FILE *leFile;
	leFile = fopen("example.spack", "r");
	if (leFile == NULL) {
		perror("File did not open\n");
		exit(EXIT_FAILURE);
	}

	// Sets file pointer to size of filename
	fseek(leFile, 4, SEEK_SET);
		
	while(1) {

		// Checks to see if at end of file
		int p = 0;
		p = getc(leFile);
		if(p == EOF) {
			fclose(leFile);
			exit(EXIT_SUCCESS);
		}
		else ungetc(p, leFile);

		// Reads in the size of file name
		fread(fileNameLen, sizeof(short), 1, leFile);

		// Reads in the file name
		char fileName[fileNameLen[0] + 1]; // Holds filename
		fread(fileName, sizeof(char), fileNameLen[0], leFile);
		fileName[fileNameLen[0]] = '\0';

		// Reads in the length of file size
		fread(&fileSize, sizeof(uint64_t), 1, leFile);
		printf("%s\n",fileName);


		// Checks to see if the file name matches
		// If it does get full path
		if((strcmp(file, fileName)) == 0) {
			char newPath[128];
			strcpy(newPath, newPath);
			strcat(newPath, "/");
			strcat(newPath, file);
			printf("%s\n", newPath);

			// Creates file to hold the selected file and error handles
			FILE *temp;
			temp = fopen(newPath, "w");
			if(temp == NULL){
				fclose(leFile);
				perror("Error: could not open new file");
				exit(EXIT_FAILURE);
			}

			uint64_t tsize = (fileSize);
			unsigned char buffer[tsize];
			fseek(leFile, -(tsize), SEEK_SET); // Backtracks current file pointer to start
			fread(buffer, sizeof(unsigned char), tsize, leFile);
			fwrite(buffer, sizeof(unsigned char), tsize, temp);

			fclose(leFile);
			fclose(temp);
			printf("Worked perfectly!!\n");
			exit(EXIT_SUCCESS);
      }
	}
}
    