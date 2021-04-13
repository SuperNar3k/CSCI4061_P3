#include "producer.h"
#include "utils.h"

/**
 *
 * Producer thread will read from the file and write data to 
 * the end of the shared queue
 */
void *producer(void* arg){
    if(printFlag) {
        fprintf("producer\n");
    }
    char* inputFileName = (char*) arg;
    //Open the file and read its content line by line
    //Send data to the shared queue
    //When reaching the end of the file, send EOF message to the sha
    int lineNumber = 0;
    int lineLen;
    char line[chunkSize];
    FILE *fp = getFilePointer(inputFileName);

    while(getLineFromFile(fp, line, chunkSize) != -1){ // reads while there are still lines in the file and adds them to the queue
        if(boundedFlag) {
            sem_wait(&slots);
        }
        pthread_mutex_lock(&lock);
        if(printFlag) {
            fprintf("producer: %d\n", lineNumber);
        }
        enqueue(queue, line);
        pthread_mutex_unlock(&lock);
        sem_post(&items);
        lineNumber++;
    }
    
    // cleanup and exit
    pthread_mutex_lock(&lock);
    queue->done = 1; // sets the done of the queue to be 1 to let consumers know the producer has reached the end of the file
    if(printFlag) {
        fprintf("producer: -1\n");
    }
    pthread_mutex_unlock(&lock);
    sem_post(&items);
    return NULL; 
}





