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
The program does something I guess.

**Assumptions:**
* Input file sizes can vary, and there is no limit.
* Make sure there is an input file for the program to read.
* Maximum size of a file path is 200 bytes
* Mmaximum word length is 20
* The chunk size to read lines will be atmost 1024 bytes

**Team names and x500s:** 
* Yna Roxas (roxas007)
* Narek Ohanyan (ohany004)
* Christopher Liu (liux3770)

**Contribution:**
* Yna Roxas: stream.c, reducer.c, part of README.md
* Narek Ohanyan: documentation, mapreducer.c, part of README.md
* Christopher Liu: mapper.c, getReducerTasks()
  
We tried our best to divide and conquer this project equally, giving each other more work if needed to make our contributions equal and fair to each other.