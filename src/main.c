#include "header.h"

/**
 * Write final word count to a single file.
 * The path name should be output/result.txt
 */
void writeFinalDSToFiles(void) {
}

int printFlag, boundedFlag, numConsumers, queueSize;
char *inputFile;


int main(int argc, char *argv[]){
    
    //Argument check
    if(argc < 2 || argc > 4) {
        printf("usage: %s <#Consumers> <inputFile> [option] [#queueSize]\n",argv[0]);
		exit(EXIT_FAILURE);
    }
    //Setup
    printFlag = 0;
    boundedFlag = 0;
    queueSize = 0;
    inputFile = argv[2];
    numConsumers = strtol(argv[1], NULL, 10);

    //Option flag setup
    if(argv[3].equals("-p")) {
        printFlag = 1;
    } else if(argv[3].equals("-b")) {
        boundedFlag = 1;
        queueSize = strtol(argv[4], NULL, 10);
    } else if(argv[3].equals("-bp")) {
        printFlag = 1;
        boundedFlag = 1;
        queueSize = strtol(argv[4], NULL, 10);
    }

    bookeepingCode();
    
    //TODO: Initialize global variables, like shared queue
    
    //TODO: create producer and consumer threads

    //TODO: wait for all threads to complete execution
    
    //Write the final output
    writeFinalDSToFiles();
    
    return 0; 
}

