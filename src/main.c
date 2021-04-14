#include "header.h"

/**
 * Write final word count to a single file.
 * The path name should be output/result.txt
 */
void writeFinalDSToFiles(void) {
    char* filePath = "output/result.txt";
    FILE* fp = fopen(filePath, "w");

    if(fp == NULL){
		exit(EXIT_FAILURE); // error opening result file
	}
    
    for (int i = 0; i < MaxWordLength; i++){
        char line[chunkSize];
        //fprintf(fp, "%d %d\n", i + 1, test[i]);
        //fprintf(fp, "%d \n", finalDS[i]);
        fprintf(fp, "%d %d\n", i + 1, finalDS[i]);
    }
    fclose(fp);
}

int main(int argc, char *argv[]){
    
    //Argument check
    if(argc < 3 || argc > 5) {
        printf("usage: %s <#Consumers> <inputFile> [option] [#queueSize]\n",argv[0]);
		exit(EXIT_FAILURE);
    }
    
    //Setup
    printFlag = 0;
    boundedFlag = 0;
    queueSize = 0;
    char *inputFile = argv[2];
    int numConsumers = strtol(argv[1], NULL, 10);

    for (int i = 0; i < MaxWordLength; i++){
        finalDS[i] = 0;
    }

    //Option flag setup
    if(argc > 3){
        if(strcmp(argv[3], "-p") == 0) {
         printFlag = 1;
        } 
        else if(strcmp(argv[3], "-b") == 0) {
            boundedFlag = 1;
            queueSize = strtol(argv[4], NULL, 10);
        } else if(strcmp(argv[3], "-bp") == 0) {
            printFlag = 1;
            boundedFlag = 1;
            queueSize = strtol(argv[4], NULL, 10);
        }
    }
    

    bookeepingCode();
    
    //Initialize global variables
    queue = malloc(sizeof(queue_t));
    queue->front = NULL;
    queue->back = NULL;
    queue->done = 0;
    queue->size = 0;
    output = fopen(logDir, "w");

    if(output == NULL){
        exit(EXIT_FAILURE); // error opening log file
    }

    if(pthread_mutex_init(&lock, NULL) != 0){
        exit(EXIT_FAILURE); // error initializing mutex lock
	}
    if(boundedFlag && sem_init(&slots, 0, queueSize) != 0){
        exit(EXIT_FAILURE); // error initializing slots semaphore
    }
    if(sem_init(&items, 0, 0) != 0){
        exit(EXIT_FAILURE); // error initializing items semaphore
    }

    //Create producer and consumer threads
    pthread_t producerThread;
    pthread_t* consumerThreads = malloc(sizeof(pthread_t) * numConsumers);

    if(pthread_create(&producerThread, NULL, producer, (void*) inputFile) != 0){
        exit(EXIT_FAILURE); // error creating producer
    }

    int *consumerIDs = malloc(numConsumers*sizeof(int));
    for (int i = 0; i < numConsumers; i++){
        consumerIDs[i] = i;
        if(pthread_create(&consumerThreads[i], NULL, consumer, &consumerIDs[i]) != 0){ 
            exit(EXIT_FAILURE); // error creating consumer
        }
    }

    //Wait for all threads to complete execution
    if(pthread_join(producerThread, NULL) != 0){
        exit(EXIT_FAILURE); // error joining producer
    }
    for (int i = 0; i < numConsumers; ++i){
        if (pthread_join(consumerThreads[i], NULL) != 0){ 
            exit(EXIT_FAILURE); // error joining consumer
        }
    } 

    //Write the final output
    writeFinalDSToFiles();
    free(consumerIDs);
    free(consumerThreads);
    free(queue);
    fclose(output);
    
    return 0; 
}
