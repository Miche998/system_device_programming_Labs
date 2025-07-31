# System and Device Programming - Laboratory 01

## Learning Goals
Review of operating system basics: processes, signals, and threads.

## Exercise 01: Process Analysis
### Description
Analyze a program using `fork()`, `exec()`, and `system()` calls. Draw process tree and explain output.

## Exercise 02: Process Tree Analysis
### Description
Analyze program with multiple `fork()` calls and `system()` commands. Draw process tree and explain output.

## Exercise 03: Complex Process Analysis
### Description
Analyze program combining `fork()`, `exec()`, and process communication. Draw process tree and explain output.

## Exercise 04: Process Tree Generator
### Description
Create a C program that:
- Takes two parameters: `h` (height) and `n` (degree)
- Generates a process tree of height `h` with `n` children per node
- Leaf processes display their PID and terminate

Example for h=2, n=2:
```
- Root process creates 2 children
- Each child creates 2 processes
- Results in 8 leaf processes
```


## Exercise 05: Binary Number Generator
### Description
Convert a recursive binary number generator into a concurrent version using processes:
- Input: number size n
- Output: all binary numbers of length n (in any order)
- Each process displays one binary number

Example output for n=3:
```
000, 001, 010, 011, 100, 101, 110, 111
```


## Exercise 06: Signal Handler
### Description
Create a signal handling program that:
- Handles SIGUSR1 and SIGUSR2
- Shows "success" for alternating signals
- Shows error for consecutive same signals
- Terminates after three consecutive same signals

## Exercise 07: Thread Tree Generator
### Description
Create a thread-based tree generator:
- Input: parameter n
- Creates binary tree of threads depth n
- Each thread creates two child threads
- Leaf threads print their ancestry chain

Example output (n=3):
```
140051327870720 140051311085312 140051224717056
...
```


## Exercise 08: Multithreaded Matrix Multiplication
### Description
Implement matrix multiplication using threads:
```c++
void mat_mul(int **A, int **B, int r, int x, int c, int **C);
```


Requirements:
- One thread per result element
- A[r,x] × B[x,c] = C[r,c]
- Each C[i,j] = Σ(A[i,k] × B[k,j]) for k=0 to x-1
- Define appropriate thread data structures