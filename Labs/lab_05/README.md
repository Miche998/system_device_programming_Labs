# System and Device Programming - Laboratory 05

## Learning Goals
Advanced I/O and concurrent programming review.

## Exercise 01: Inter-Process Communication
### Description
Create two communicating processes using shared memory and synchronization:

P1 Process:
1. Generates random size n
2. If n=0: terminate both processes
3. If n>0:
   - Generate random text of length n
   - Signal P2 via pipe
   - Wait for P2's response
   - Convert received text to uppercase
4. Repeat

P2 Process: 
- Mirror of P1 but starts by waiting

### Versions
1. Version A: Using pipes
2. Version B: Using FIFOs
3. Version C: Using message queues

## Exercise 02: Optimized Concurrent Sorting
### Description
Improve Lab 04's sorting program:

Changes:
- Main thread merges results immediately when available
- No waiting for all threads to complete
- Progressive merging of sorted sequences

### Performance Analysis
Compare execution times:
- Generate large test files
- Measure using time.h/clock()
- Compare with previous version

## Exercise 03: Matrix Operations
### Description
Implement matrix multiplication: res = v1^T * mat * v2

Example input (n=5):
```
v1^T = [-0.0613 -0.1184  0.2655  0.2952 -0.3131]
mat  = [-0.3424 -0.3581  0.1557  0.2577  0.2060
         0.4706 -0.0782 -0.4643  0.2431 -0.4682
         ...]
v2^T = [-0.3235  0.1948 -0.1829  0.4502 -0.4656]
```


### Implementation Versions
1. Sequential Version
2. Concurrent Version A:
   - Main thread: setup and final multiplication
   - N worker threads: row operations
3. Concurrent Version B:
   - Like Version A
   - Last finishing thread performs final multiplication