# Producer–Consumer Problem (Shared Memory & Semaphores)

## Overview
This project implements the classic Producer–Consumer problem using POSIX shared memory and semaphores in C/C++.  
Two separate processes producer and consumer share a common memory region the table.  
The producer adds items to the table, and the consumer removes them, both synchronized to prevent race conditions.

## Files
`producer.cpp` Creates shared memory and produces items.
`consumer.cpp` Connects to shared memory and consumes items.
`shared.h` Defines the shared memory structure used by both programs.


## Compilation
You can compile using g++ with pthreads and real-time libraries:
g++ producer.cpp -pthread -lrt -o producer
g++ consumer.cpp -pthread -lrt -o consumer
