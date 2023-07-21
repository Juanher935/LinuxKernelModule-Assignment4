# LinuxKernelModule-Assignment4

**Part 1 Sudoku Solution Validator:**

Each worker thread is assigned the task of determining the validity of a particular region of the Sudoku puzzle. Once a worker has performed this check, it must pass its results back to the parent. One good way to handle this is to create an array of integer values that is visible to each thread. The index in this array corresponds to the i<sup>th</sup> worker thread. If a worker sets its corresponding value to 1, it is indicating that its region of the Sudoku puzzle is valid. A value of 0 would indicate otherwise. When all worker threads have been completed, the parent thread checks each entry in the result array to determine if the Sudoku puzzle is valid.


**Part 2 Multithreaded Sorting Application:**

Write a multithreaded sorting program that works as follows: A list of integers is divided into two smaller lists of equal size. Two separate threads (which we will term sorting threads) sort each sublist using a sorting algorithm of your choice. The two sublists are then merged by a third thread-a merging thread -which merges the two sublists into a single sorted list.
Because global data are shared across all threads, perhaps the easiest way to set up the data is to create a global array. Each sorting thread will work on one-half of this array. A second global array of the same size as the unsorted integer array will also be established. The merging thread will then merge the two sublists into this second array. This programming project will require passing parameters to each of the sorting threads. In particular, it will be necessary to identify the starting index from which each thread is to begin sorting. The parent thread will output the sorted array once all sorting threads have exited.
