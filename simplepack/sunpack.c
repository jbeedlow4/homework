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
        //If this is true...the user requested
        //a list of the files in flags.packfile
        //so open it up, find all the filenames
        //and file sizes and print them out.
        //assume flags.packfile variable is the full
        //path to the packed file to list.
        printf("Listing files in %s.\n", flags.packfile);
    }
    
    else if(flags.extract && flags.extract_single){
        //If this is the case, then we open up the pack file,
        //and look at each file until we find one with the
        //same name as the one requested by the user (strcmp).

        //If the requested file name isn't found in the pack
        //file, then you need to print an error message and
        //return a non-zero value! This is very important!
        printf("Extracting just %s from %s into %s\n", flags.file_name, flags.packfile, flags.dest);
    }
    
    else if( flags.extract ){
        
        //If this is the case, then we just want to open the
        //pack file, and for each file we find in it, we write
        //it out to the directory specified in flags.dest
        printf("Extracting all files from %s into %s\n", flags.packfile, flags.dest);
    }

    //Only return 0 if everything succeeded!
    return 0;
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
void print_file_record(char *fname, long long fsize){
    printf("%-20lld\t%s\n", fsize, fname);
}
