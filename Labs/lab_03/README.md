# System and Device Programming - Laboratory 03

## Learning Goals
Advanced File and File-system I/O operations.

## Preliminary Concepts: PIPES
Pipes provide basic inter-process communication:
- Acts as a "pseudo-file"
- One process writes, another reads
- Blocking operations by default
- Creation syntax:
```c++
int fd[2];
pipe(fd);  // fd[0] for reading, fd[1] for writing
```


## Exercise 01: Multi-Version I/O Implementation
### Description
Create a program with three processes:

Parent Process (P):
- Creates two child processes
- Reads from two pipes
- Converts received strings to uppercase
- Displays results

Child Process 1 (C1):
- Waits WAIT_TIME_1 seconds between operations
- Generates random strings (max STR_SIZE length)
- Writes STR_NUM strings to pipe p1

Child Process 2 (C2):
- Similar to C1 but with WAIT_TIME_2 delay
- Writes to pipe p2

### Implementation Versions
1. **Version A**: Blocking I/O
2. **Version B**: Non-blocking I/O
3. **Version C**: Multiplexed I/O
4. **Version D**: Asynchronous I/O

### Communication Protocol
Recommended approach:
1. Write string length (integer)
2. Write string content
3. Read length then content

## Exercise 02: Memory-Mapped File Processing
### Description
Process a binary file using memory mapping and threads.

Input file format example:
```
1 100000 Romano Antonio 25
2 150000 Fabrizi Aldo 22
3 200000 Verdi Giacomo 15
4 250000 Rossi Luigi 30
```


Requirements:
1. Map file into memory
2. Create two threads:
   - Thread 1: Forward traversal, increment register numbers
   - Thread 2: Backward traversal, decrement marks