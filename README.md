# Linux Process Simulator by Yasir Jami & Cole Doris
### graphics.py written by John Zelle and released under the GPL:
#### Source code: https://mcsp.wartburg.edu/zelle/python/graphics.py
#### Reference: https://mcsp.wartburg.edu/zelle/python/graphics/graphics.pdf

### This is a program that simulates the queueing and running of processes on a Linux system.

#### Files in the newProc directory represent processes and contain two values: niceness and proctime.
- Niceness determines the process's priority (only for MLFQ).
- Proctime is an estimated value that determines how long the process will run.

#### These processes are enqueued to a ready queue and are run on a running queue according to a specified scheduling algorithm.

## There are 4 scheduling algorithms that can be simulated:
- Shortest Job First (SJF)
- First-in First-out (FIFO)
- Round Robin (RR)
- Multi-level Feedback Queue (MLFQ)

### The scheduling algorithms enqueue processes from the ready queue to the running queue in order of:
#### SJF: the processes with the shortest process time (proctime).
#### FIFO: the first processes in the ready queue.
#### RR: in the same manner as FIFO but it also periodically dequeues processes that run for a specified amount of time and enqueues the next one.
#### MLFQ: also in the same manner as FIFO but it instead adds processes to a "niceness queue" that enqueues processes according to their niceness instead of a ready queue.

### As the program runs, the status of each process is logged in 0.1 sec increments in a file that specifies the date and algorithm used. These increments are simulated, and do not reflect real time. 

#### Once the program has finished running, plotData.py can be used to plot a graph that is extracted from the produced log file.

![image](https://github.com/Yasir-Jami/360-Project/assets/73759953/fbfe1265-eb47-45c2-ae51-637555b3a721)
