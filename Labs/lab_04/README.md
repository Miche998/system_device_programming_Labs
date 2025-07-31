# System and Device Programming - Laboratory 04

## Learning Goals
Advanced programming with:
- Binary files
- File systems
- Multi-threaded programming with advanced synchronization

## Prerequisites
- Sorting algorithms (insertion sort, quick sort, etc.)
- Merge algorithm for ordered sequences

## Exercise 01: Parallel Prefix Sum
### Description
Create a multi-threaded program to compute prefix sums:
- Input: Array of 2^n elements
- Output: Cumulative sum array

Example for n=3 (8 elements):
```
Initial:  2  4  6  1  3  5  8  7
Step 1:   2  6 10  7  4  8 13 15  (gap=1)
Step 2:   2  6 12 13 14 15 17 23  (gap=2) 
Step 3:   2  6 12 13 16 21 29 36  (gap=4)
```


### Requirements
1. Main thread handles array initialization
2. Use concurrent threads for computation
3. Update array in-place
4. Maximum n iterations per thread
5. Early thread termination based on position
6. Ordered output printing

## Exercise 02: Multi-threaded File Sorting
### Description
Process multiple binary files containing integers:
- First integer = count of remaining numbers
- Remaining numbers = data to sort

Example input files:
```
File 1: 5 23 45 67 9 23
File 2: 12 90 65 34 24 12 0 89 29 54 12 78 3
File 3: 3 9 5 1
```


### Requirements
1. Multiple input files, one output file
2. One sorting thread per input file
3. Main thread merges sorted results
4. Binary file I/O
5. Final output in ascending order

## Exercise 03: Directory Tree Comparison
### Description
Compare multiple directory trees for content equality:
- Input: N directory paths
- Output: Whether all trees have matching content

### Implementation
1. One reader thread per directory
2. One comparing thread
3. Synchronized directory traversal
4. Name-based comparison (ignoring paths)

### Termination Cases
1. All directories match
2. Name mismatch found
3. Different entry counts

### Thread Coordination
- Readers synchronize at each entry
- Comparator validates entry names
- Early termination on mismatch
- Handle unequal directory sizes