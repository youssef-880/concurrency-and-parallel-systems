Concurrency & Parallel Performance Studies
This repository contains two core projects exploring the fundamentals of Concurrent Programming and System Performance Optimization. The projects transition from low-level thread management in C to high-level parallel benchmarking in Python.

📂 Project 1: Multithreaded Task Processor (C)
A system simulation designed to demonstrate the "Worker-Thread" architecture. It addresses the complexities of shared resources and data integrity in a multithreaded environment.  

Key Concepts
Thread Management: Utilizing POSIX threads (pthreads) for concurrent execution.  

Race Conditions: Understanding and preventing unpredictable behavior when multiple threads access shared memory simultaneously.  

Synchronization: Implementing four distinct methods to coordinate thread activity:  

Mutex Locks: Ensuring mutual exclusion during critical section access.  

Semaphores: Controlling the signaling and availability of tasks in the queue.  

Thread Joining: Synchronizing the main process with worker completion.  

Condition Logic: Managing thread-safe task distribution.


📂 Project 2: Performance & Efficiency Benchmark (Python)
An analytical tool used to measure and compare the execution speeds of sequential versus parallel processing using a CPU-bound task.

Key Concept:
Parallelism: Leveraging the multiprocessing module to bypass the Global Interpreter Lock (GIL) and utilize all CPU cores.  

Computation: Calculating prime numbers up to a specified limit to create a heavy mathematical workload.

Performance Metrics:
Speedup: Calculated as $S = T_{sequential} / T_{parallel}$ to show the factor of improvement.  
Efficiency: Calculated as $E = S / N$ (where $N$ is the number of cores) to measure hardware utilization. 
