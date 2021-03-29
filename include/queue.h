#ifndef QUEUE_H
#define QUEUE_H

typedef struct node{
  char* line;
  struct node* next;
}node_t;

typedef struct queue{
  struct node* front;
  struct node* back;
}queue_t;

void enqueue(queue_t* queue, char* line);

void dequeue(queue_t* queue, char* buf);

#endif