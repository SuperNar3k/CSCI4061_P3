#include "header.h"

/**
 * Write final word count to a single file.
 * The path name should be output/result.txt
 */
void writeFinalDSToFiles(void) {
    char* filePath = "output/result.txt";
    for (int i = 0; i < MaxWordLength; i++){
        char line[chunkSize];
        sprintf(line, "%d %d\n", i + 1, finalDS[i]);
        writeLineToFile(filePath, line);
    }
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
    if(strcmp(argv[3], "-p") == 0) {
        printFlag = 1;
    } else if(strcmp(argv[3], "-b") == 0) {
        boundedFlag = 1;
        queueSize = strtol(argv[4], NULL, 10);
    } else if(strcmp(argv[3], "-bp") == 0) {
        printFlag = 1;
        boundedFlag = 1;
        queueSize = strtol(argv[4], NULL, 10);
    }

    bookeepingCode();
    
    //TODO: Initialize global variables, like shared queue
    queue = malloc(sizeof(queue_t));
    queue->front = NULL;
    queue->back = NULL;
    queue->done = 0;

    //TODO: create producer and consumer threads
    pthread_t producerThread;
    pthread_t* consumerThreads = malloc(sizeof(pthread_t) * numConsumers);

    pthread_create(&producerThread, NULL, producer, (void*) inputFile);

    for (int i = 0; i < numConsumers; i++){
        pthread_create(&consumerThreads[i], NULL, consumer, (void*) queue);
    }

    //TODO: wait for all threads to complete execution
    pthread_join(producerThread, NULL);
    for (int i = 0; i < numConsumers; ++i){
        pthread_join(consumerThreads[i], NULL); //wait for all the threads to be finished
    } 

    //Write the final output
    writeFinalDSToFiles();
    
    return 0; 
}
