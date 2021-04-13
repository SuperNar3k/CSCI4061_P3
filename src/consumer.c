#include "consumer.h"

/**
 * parse lines from the queue, and count words by word length
 */
void parse(int* interDS){
    char line[chunkSize];
    dequeue(queue, line);
    int wordLen = 0;
    int lineLen = strlen(line);
    for (int i = 0; i < lineLen; i++){            
        // records the length of a word once whitespace or a newline is found
        if (line[i] == ' ' || line[i] == '\n'){
            interDS[wordLen - 1]++;
            wordLen = 0;
        } else{
            wordLen++;
        }
    }
    interDS[wordLen - 1]++; // add length of the last word on the last line
}

// consumer function
void *consumer(void *arg){
    if(printFlag) {
        fprintf("consumer %d\n", *(int *)arg);
    }
    int interDS[MaxWordLength];

    while(1){
        sem_wait(&items);
        pthread_mutex_lock(&lock);
        if (queue->done && (queue->size <= 0)){ // producer has finished reading and the queue is empty
            pthread_mutex_unlock(&lock);
            sem_post(&items);
            break;
        }
        if(printFlag) {
            //TODO!!!! FIX LINENUM SO IT ACTUALLY WORKS LMAO
            fprintf("consumer %d: %d\n", *(int *)arg, lineNum);
        }
        parse(interDS);
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


