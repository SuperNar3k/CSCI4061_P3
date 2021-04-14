# UMN CSCI 4061 Project 3
## Multithreading
## Spring 2021

**Purpose:** 
This program uses multithreading to create a producer thread to read the file, and multiple consumer threads to process the smaller pieces of data. There are two forms of synchronization: a shared queue synchronized between producer and consumers, and a global result histogram synchronized by consumers.

**How to compile:**  
`make clean`  
`./mapreduce #consumers inputFile [option] [#queuesize]`
The first argument `#consumers` is the number of consumers the program will create. The second argument `inputFile` is the input file name. The third, optional, argument has three options: `-p` (the program will generate a log), `-b` (the program will use a bounded buffer instead of an unbounded buffer), `-bp` (both bounded buffer and log printing). The final argument `#queuesize` is the queue size if the bounded buffer option is used.

**What this does:**
This program uses multithreading in order to read a file that contains data and processes the data into a histogram. a master thread is first initialized and is used to create the shared queue, histogram, and one producer and consumer thread. The producer then reads the input one line at a time, splits the data into smaller bits, and then feeds the data into the queue. The consumers read into the queue, computes the word length stats of the data, and then synchronizes the result with the global histogram. Once all the producers and consumers finish, the master thread writes the final result into the output text file. The accessing of data is controlled by using semaphores and mutex locks so each producer and consumer thread take turns looking at the data. 

**Assumptions:**
* Input file sizes can vary, and there is no limit.
* Make sure there is an input file for the program to read.
* Maximum size of a file path is 200 bytes.
* Mmaximum word length is 20.
* The chunk size to read lines will be atmost 1024 bytes.
* If the bounded buffer option is used, but no buffer size is inputted, it will default to a bounded size of 10.

**Team names and x500s:** 
* Yna Roxas (roxas007)
* Narek Ohanyan (ohany004)
* Christopher Liu (liux3770)

**Contribution:**
* Yna Roxas: documentation, README.md, main.c, producer.c
* Narek Ohanyan: main.c, README.md, bounded buffer
* Christopher Liu: getReducerTasks(), consumer.c, producer.c, header files
  
We tried our best to divide and conquer this project equally, giving each other more work if needed to make our contributions equal and fair to each other.