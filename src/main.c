#include "header.h"

 // Outputs word count to a file with a path named output/result.txt
void writeFinalDSToFiles(void) {
    char* filePath = "output/result.txt";
    FILE* fp = fopen(filePath, "w");
    
    for (int i = 0; i < MaxWordLength; i++){
        char line[chunkSize];
        fprintf(fp, "%d %d\n", i + 1, finalDS[i]);
    }
    fclose(fp);
}

int main(int argc, char *argv[]){
    
    // Check if all arguments are present
    if(argc < 3 || argc > 5) {
        printf("usage: %s <#Consumers> <inputFile> [option] [#queueSize]\n",argv[0]);
		exit(EXIT_FAILURE);
    }
    
    // Initialize variables
    printFlag = 0;
    boundedFlag = 0;
    queueSize = 0;
    char *inputFile = argv[2];
    int numConsumers = strtol(argv[1], NULL, 10);

    // clear out the array used to write to end file
    for (int i = 0; i < MaxWordLength; i++){
        finalDS[i] = 0;
    }

    // Optional flag setups
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
    
    // Initialize global variables
    queue = malloc(sizeof(queue_t));
    queue->front = NULL;
    queue->back = NULL;
    queue->done = 0;
    queue->size = 0;
    output = fopen(logDir, "w");

    pthread_mutex_init(&lock, NULL);
    if(boundedFlag){
        sem_init(&slots, 0, queueSize);
    }
    sem_init(&items, 0, 0);

    // For each producer, create a producer thread
    pthread_t producerThread;
    pthread_t* consumerThreads = malloc(sizeof(pthread_t) * numConsumers);

    pthread_create(&producerThread, NULL, producer, (void*) inputFile);

    int *consumerIDs = malloc(numConsumers*sizeof(int));
    // For each consumer, create a consumer thread
    for (int i = 0; i < numConsumers; i++){
        consumerIDs[i] = i;
        pthread_create(&consumerThreads[i], NULL, consumer, &consumerIDs[i]);
    }

    // Wait for all threads to complete execution
    pthread_join(producerThread, NULL);
    for (int i = 0; i < numConsumers; ++i){
        pthread_join(consumerThreads[i], NULL); // wait for all the threads to be finished
    } 

    //Write the final output
    writeFinalDSToFiles();
    // Free memory
    free(consumerIDs);
    free(consumerThreads);
    free(queue);
    fclose(output);
    
    return 0; 
}
