#include "producer.h"


 // Producer thread will read from the file and write data to the end of the shared queue

void *producer(void* arg){
    char* inputFileName = (char*) arg;
    // Send data to the shared queue
    // When reaching the end of the file, send EOF message to the shared queue
    int lineNum = 0;
    char line[chunkSize];
    FILE *fp = getFilePointer(inputFileName);

    if(fp == NULL){
        exit(EXIT_FAILURE); // error opening input file
    }

    if(printFlag){
        fprintf(output, "producer\n");
    }

    // reads while there are still lines in the file and adds them to the queue
    // uses semaphores and mutex locks to handle access of data
    while(getLineFromFile(fp, line, chunkSize) != -1){ e
        if(boundedFlag){
            sem_wait(&slots);
        }
        pthread_mutex_lock(&lock);
        if(printFlag){
            fprintf(output, "producer: %d\n", lineNum);
        }
        enqueue(queue, line, lineNum);
        pthread_mutex_unlock(&lock);
        sem_post(&items);
        lineNum++;
    }
    
    // cleanup and exit
    pthread_mutex_lock(&lock);
    // Set the `done` of the queue to be 1 to let consumers know the producer has reached the end of the file
    queue->done = 1; 
    if(printFlag){
        fprintf(output, "producer: -1\n");
    }
    pthread_mutex_unlock(&lock);
    sem_post(&items);
    fclose(fp);
    return NULL; 
}





