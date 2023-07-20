#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sudoku[9][9] = {
        {6, 2, 4, 5, 3, 9, 1, 8, 7},
        {5, 1, 9, 7, 2, 8, 6, 3, 4},
        {8, 3, 7, 6, 1, 4, 2, 9, 5},
        {1, 4, 3, 8, 6, 5, 7, 2, 9},
        {9, 5, 8, 2, 4, 7, 3, 6, 1},
        {7, 6, 2, 3, 9, 1, 4, 5, 8},
        {3, 7, 1, 9, 5, 6, 8, 4, 2},
        {4, 9, 6, 1, 8, 2, 5, 7, 3},
        {2, 8, 5, 4, 7, 3, 9, 1, 6}
};

/* You will need to declare an array of integer values that is visible to each thread. The value in the array (0 or 1) indicates whether the worker thread's number is valid (see "Returning Results to the Parent Thread" in the textbook's project description) */
int valid[11]; //When the threads are joined, if that thread is a valid part of a sudoku puzzle, it returns 1 to valid[], else it returns 0
int subgridCt = 2; //used to track through valid array sections for the 3x3 subgrids


/* You will need a structure to store the information to be passed to each thread (see "Passing Parameters to Each Thread" in the textbook's project description)*/
typedef struct{
    
    int row;
    int column;
    
}parameters;

//declare the threads
pthread_t col_thread, row_thread, first_thread, second_thread, third_thread, fourth_thread, fifth_thread, sixth_thread, seventh_thread, eighth_thread, ninth_thread;

