#include "utils.h"
// pthread.h included in header.h

// Feel free to add any functions or global variables
void enqueue(queue_t* queue, char* line, int lineNum){
  node_t* newNode = malloc(sizeof(struct node));
  int lineLen = strlen(line) + 1;
  newNode->line = malloc(lineLen);
  strcpy(newNode->line, line);
  
  newNode->next = NULL;
  newNode->lineNum = lineNum;

  if(queue->front == NULL){ // queue is empty
    queue->front = newNode;
    queue->back = newNode;   
  } 
  else{
    queue->back->next = newNode;
    queue->back = newNode;
  }
  queue->size++;
}

node_t* dequeue(queue_t* queue){
  if(queue->front == NULL){ // Queue is empty
    return NULL;
  }

  node_t* front = queue->front;
  queue->front = queue->front->next;

  if(queue->front == NULL){ // There was only one item in the queue
    queue->back = NULL;
  }

  queue->size--;
  return front;
}

int isValidFile(char* inputFileName){
  struct stat sb;
  return (stat(inputFileName, &sb) == 0 && S_ISREG(sb.st_mode));
}

/* File operations */
void writeLineToFile(char *filepath, char *line) {
    int fd = open(filepath, O_CREAT | O_WRONLY | O_APPEND, 0777);
    if (fd < 0){
        printf("ERROR: Cannot open the file %s\n", filepath);
        fflush(stdout);
        exit(EXIT_FAILURE);
    }
    int ret = write(fd, line, strlen(line));
    if(ret < 0){
        printf("ERROR: Cannot write to file %s\n", filepath);
        fflush(stdout);
        exit(EXIT_FAILURE);
    }
}

FILE * getFilePointer(char *inputFileName) {
    return fopen(inputFileName, "r");
}

ssize_t getLineFromFile(FILE *fp, char *line, size_t len) {
    memset(line, '\0', len);
    return getline(&line, &len, fp);
}

void _removeOutputDir(){
    pid_t pid = fork();
    if(pid == 0){
        char *argv[] = {"rm", "-rf", "output", NULL};
        if (execvp(*argv, argv) < 0) {
            printf("ERROR: exec failed\n");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    } else{
        wait(NULL);
    }
}

void _createOutputDir(){
    mkdir("output", ACCESSPERMS);
}

void bookeepingCode(){
    _removeOutputDir();
    sleep(1);
    _createOutputDir();
}