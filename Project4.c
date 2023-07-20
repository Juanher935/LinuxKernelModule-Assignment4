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

//Check if a sub-grid is valid (3x3)
void *checkRegion(void *arg){
    parameters *param = (parameters *)arg;
    int row = param->row;
    int col = param->column;
    int rowStart = row * 3;
    int colStart = col * 3;
    int seen[10] = {0};

    // Iterate over the sub-grid
    for (int i = rowStart; i < rowStart + 3; i++)
    {
        for (int j = colStart; j < colStart +3; j++)
        {
            int num = sudoku[i][j];
            if (seen[num] == 1)
            {
                pthread_exit(NULL); // If a number is repeated, region is invalid
            }
            seen[num] = 1;
        }
        
    }
    // If the loop completes the region is valid
    valid[row * 3 + col] = 1;
    pthread_exit(NULL);
}

int main(){
    //Array to hold the worker threads IDs
    pthread_t threads[11];

    //Create worker threads to check each region
    parameters params[11] = {
        {0, 0}, {0, 1}, {0, 2},
        {1, 0}, {1, 1}, {1, 2},
        {2, 0}, {2, 1}, {2, 2}
    };

    for (int i = 0; i < 9; i++)
    {
        pthread_create(&threads[i], NULL, checkRegion, (void *)&params[i]);
    }

    // Wait for threads to complete
    for (int i = 0; i < 9; i++)
    {
        pthread_join(threads[i], NULL);
    }
    
    int isValid = 1;
    for (int i = 0; i < 9; i++)
    {
        if (valid[i] == 0)
        {
            isValid = 0;
            break;
        }
        
    }
    
    //sends the Output
    if (isValid)
    {
        printf("Sudoku Puzzle is Valid\n");
    }
    else{
        printf("Sudoku Puzzle is Not Valid!\n");
    }
    
    return 0;
}