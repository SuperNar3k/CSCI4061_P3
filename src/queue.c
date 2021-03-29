#include "queue.h"

void enqueue(queue_t* queue, char* line){
  struct node_t* newNode = malloc(sizeof(struct node));
  newNode->line = line;
  newNode->next = NULL

  if(queue->front == NULL){ // queue is empty
    queue->front = newNode;
    queue->back = newNode;
  } 
  else{
    queue->back->next = newNode;
    queue->back = newNode;
  }

  
}

void dequeue(queue_t* queue, char* buf){
  if(queue->front == NULL){ // Queue is empty
    return NULL;
  }

  node_t* front = queue->front;
  queue->front = queue->front->next;

  strcpy(buf, front->line);
  free(front);

  if(queue->front == NULL){ // There was only one item in the queue
    queue->back = NULL;
  }
}