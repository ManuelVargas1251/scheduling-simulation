![Programming language](https://img.shields.io/badge/Language-C++-black.svg)
![Version](https://img.shields.io/badge/Version-1.3-blue.svg)

# Scheduling Simulation
CSCE 4600 Operating Systems

Implement Round Robin as well as two other scheduling disciplines. 

## Instructions
Using the process generator that you developed in Homework #2, generate a set of 50 processes with different runtime requirements (i.e., cycles). You may assume that the processes arrive in the system every 50 cycles (e.g., at times 0, 50,100, 150, 200, …etc.)

1. Develop a simulation of Round-Robin Scheduling with a quantum of 50 cycles, and schedule your set of processes. Assuming a context switch penalty of 10 cycles (for the scheduler to switch between processes), compute the average waiting time and the total penalty for the set of processes. Repeat the experiment over different sets of processes. You should document (graphically) the distribution of cycle times for your set of processes.

2. Repeat the experiment above for 2 additional scheduling disciplines (SRT, SJF, FIFO, LRT).

3. Assuming that you have a multi-processor system with 4 processors. Repeat the above experiments and calculate the average waiting time and total context-switch penalty.

## Deliverables
Write a 5-page report that highlights the performance and differences of the scheduling algorithms. You must discuss all the limitations and assumptions. In detail, show how you analyzed the performance (i.e., average waiting time) and present your results. You must submit well-documented code along with specification of any special compilation procedures.