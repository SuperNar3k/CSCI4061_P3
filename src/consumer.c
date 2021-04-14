#include "consumer.h"


 // Parse lines from the queue, and count words by word length. Returns the line number of the item read from the queue.
 

int parse(int* interDS){
    // Initialize variables, store next data to be read into a node and also copy it into a string
    char line[chunkSize];
    node_t* node = dequeue(queue);
    strcpy(line, node->line);
    // More initialization of variables
    int lineNum = node->lineNum;
    int wordLen = 0;
    int lineLen = strlen(line);

    // Iterate through each line
    for (int i = 0; i < lineLen; i++){            
        // records the length of a word once whitespace or a newline is found
        if (line[i] == ' ' || line[i] == '\n'){
            interDS[wordLen - 1]++;
            wordLen = 0;
        } else{
            wordLen++;
        }
    }

    // add length of the last word on the last line
    interDS[wordLen - 1]++; 
    // Free data
    free(node->line);
    free(node);
    return lineNum;
}

// consumer function
void *consumer(void *arg){
    int consumerID = *(int *) arg;

    if(printFlag) {
        fprintf(output, "consumer %d\n", consumerID);
    }
    int interDS[MaxWordLength];

    // Use semaphores and mutex locks to access the data and write to the histogram
    while(1){
        sem_wait(&items);
        pthread_mutex_lock(&lock);
        if (queue->done && (queue->size <= 0)){ // producer has finished reading and the queue is empty
            fprintf(output, "consumer %d: -1\n", consumerID);
            pthread_mutex_unlock(&lock);
            sem_post(&items);
            break;
        }

        int lineNum = parse(interDS);

        if(printFlag) {
            //printf("consumer %d: %d\n", consumerID, lineNum);
            fprintf(output, "consumer %d: %d\n", consumerID, lineNum);
        }
        pthread_mutex_unlock(&lock);

        if(boundedFlag) {
            sem_post(&slots);
        }
    }
    
    //Update the global array
    pthread_mutex_lock(&lock);
    for (int i = 0; i < MaxWordLength; i++){
        finalDS[i] += interDS[i];
    }
    pthread_mutex_unlock(&lock);
    return NULL; 
}


