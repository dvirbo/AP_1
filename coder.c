#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include "codec.h"
#include <stdint.h>
#include <string.h>

/*
* Struct which holds the data/each task of each thread
* so it's easier to pass instructions to workers
*/
typedef struct Data {
    int key;
    char *_flag;
	char *message;
} Data;

#define BUFFERSIZE 1024 // Given buffer size (1024!!!!#!@#!@#$)

char* flag; // For -d or -e


int main(int argc, char *argv[]){
	/**
	 * Less than 3 arguments
	*/
	if(argc != 3) {
		printf("Too few arguments ");
		printf("USAGE: ./coder <key> < -e or -d for encrypt/decrypt>");
		exit(0);
	}

	// Get args from input (key & flag)
	int given_key = atoi(argv[1]); // given key
	flag = argv[2]; // -d or -e

	// Input file/object/whatever
    char buffer[BUFFERSIZE]; // 1024 as mentioned
	char *str;
    while(fgets(buffer, BUFFERSIZE , stdin) != NULL){
		Data t = {
			.key = given_key,
            ._flag = flag,
			.message = str
        };
	};
	int n = sysconf(_SC_NPROCESSORS_ONLN); // Number of processors 

	

	
	return 0;
}

