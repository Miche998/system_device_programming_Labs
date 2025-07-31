# System and Device Programming - Laboratory 02

## Learning Goals
File and filesystem basics with thread concurrency.

## Exercise 01: Binary Files

### Description
An ASCII file has lines with the following format:
- ID: integer value (1 to N)
- Register number: 6-digit long integer (e.g., 164678)
- Surname: string (max 30 chars)
- Name: string (max 30 chars)
- Exam mark: integer value

Example file content:
```
1 100000 Romano Antonio 25
2 150000 Fabrizi Aldo 22
3 200000 Verdi Giacomo 15
4 250000 Rossi Luigi 30
```


### Requirements
Create a C program that accepts 3 filenames as arguments (`file_1 file_2 file_3`):
1. Read text from `file_1` and save as binary in `file_2` (fixed-length records)
2. Read binary from `file_2` and save as text in `file_3`

### Tips
- Use C library for text files and UNIX I/O for binary files
- Verify equivalence using `wc` and `diff` commands

## Exercise 02: Random File Walks

### Description
Create a program for binary file manipulation with these commands:
- `R n`: Read and display record n
- `W n`: Write new data to record n
- `E`: Exit program

### Example Usage
```
> R 3     # Read record 3
3 200000 Verdi Giacomo 15
> W 1     # Write to record 1
Data: 1 100000 Romano Antonio 27
> E       # Exit
```


## Exercise 03: Directory Copy with Modification

### Description
Implement `cp -R` with additional features:
- Input: `dir_1 dir_2` (source and destination paths)
- Copy directory tree from `dir_1` to `dir_2`
- Add metadata to each copied file:
  - Filename (without path)
  - Original file size

## Exercise 04: Parallel Directory Visit

### Description
Create a multi-threaded directory visitor:
- Accept N directory paths
- Create N threads (one per directory)
- Each thread visits its directory recursively
- Main thread waits for completion

### Versions

#### Version A
- Basic implementation
- Direct output to stdout (interleaved)

#### Version B
- Thread-specific output files
- Main thread consolidates output

#### Version C (Future)
- Centralized output thread
- Critical section implementation
- Enhanced output management:
  - File-based storage
  - Message sorting
  - Verbosity control
  - Statistics generation