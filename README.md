# Process Scheduler
* Program simulating the CPU scheduler found on a typical Linux-based system. 

* The program uses files representing processes to simulate execution and context switching according to the specified scheduling algorithm. 

* The status of each process is recorded from the instant the first process is dispatched to the ready queue up to the program's completion in a log file. The filename of the log is in the format: `logfile-MM-DD-YYYY-ALGORITHM`, which notes the date the program was run and the algorithm used.

#### Files in the newProc directory representing processes contain two values: niceness and proctime.
* Niceness determines the process's priority in multi-level feedback queues.
* Proctime is an estimate of how long the process will run and, in effect, how long it runs in this simulator.

#### Scheduling Algorithms
By default, the algorithms push processes from the ready queue to the running queue using First-In First-Out (FIFO) rules; the processes placed on the ready queue first are executed first:
- First-in First-out (FIFO): default scheduling method.
- Shortest Job First (SJF): exception to FIFO method, processes with the shortest process time (proctime) are enqueued first.
- Round Robin (RR): periodically switches out processes that run for a certain amount of time with the next one.
- Multi-level Feedback Queue (MLFQ): processes use a "niceness queue" to determine process execution: processes in queues with higher niceness run first and move between queues dynamically. All niceness queues periodically reset, returning processes to their original queues after a specified amount of time has passed.

<b>As the program runs, the status of the processes currently in a queue is logged in 0.1 sec increments in a file. These increments are simulated and do not reflect real time. Once the program has finished running, the log file can be read by `plotData.py` to plot a graph that shows the performance of the selected algorithm.<b>

<div align="center">
   <img src="https://github.com/Yasir-Jami/360-Project/assets/73759953/fbfe1265-eb47-45c2-ae51-637555b3a721"></img>
</div>

---
### graphics.py written by John Zelle and released under the GPL.
* Source code: https://mcsp.wartburg.edu/zelle/python/graphics.py
* Reference: https://mcsp.wartburg.edu/zelle/python/graphics/graphics.pdf
