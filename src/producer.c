#include "producer.h"
#include "utils.h"

/**
 *
 * Producer thread will read from the file and write data to 
 * the end of the shared queue
 */
void *producer(char * inputFileName){
    
    //TODO: open the file and read its content line by line
    //Send data to the shared queue
    //When reaching the end of the file, send EOF message to the sha
    int lineLen;
    char line[chunkSize];
    FILE *fp = getFilePointer(inputFileName);
    while((lineLen = getLineFromFile(fp, line, chunkSize)) != -1){ // Reads while there are still lines in the file
        pthread_mutex_lock();
        enqueue(queue, lineLen);
        pthread_mutex_unlock();
    // cleanup and exit
    return NULL; 
}





