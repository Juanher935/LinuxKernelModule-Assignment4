#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

// Global array for unsorted and sorted arrays
int sortedArray[SIZE];

//Structure to pass parameters to the sorting threads
typedef struct
{
    int start;
    int end;
} SortParameters;

//Merge two sorted subarrays into a single array
void merge(int start, int mid, int end){
    int leftSize = mid - start + 1;
    int rightSize = end - mid;

    int leftArray[leftSize], rightArray[rightSize]; //creating up left and right side of the main array

    for (int i = 0; i < leftSize; i++)
    {
        leftArray[i] = sortedArray[start + i];
    }

    for (int i = 0; i < rightSize; i++)
    {
        rightArray[i] = sortedArray[mid + 1 + i];
    }

    int i = 0, j = 0, k = start;

    while (i < leftSize && j < rightSize)
    {
        if (leftArray[i] <= rightArray[j]) {
            sortedArray[k] = leftArray[i];
            i++;
        } else {
            sortedArray[k] = rightArray[j];
            j++;
        }
        k++;      
    }
    
    while (i < leftSize)
    {
        sortedArray[k] = leftArray[i];
        i++;
        k++;
    }
    
    while (j < rightSize)
    {
        sortedArray[k] = rightArray[j];
        j++;
        k++;
    }
}

// Merge Sort Function
void mergeSort(int start, int end){
    if (start < end)
    {
        int mid = (start + end) / 2;
        mergeSort(start, mid);
        mergeSort(mid + 1, end);
        merge(start, mid, end);
    }
}

// Function used by each sorting thread
void *sortThread(void *arg){
    SortParameters *params = (SortParameters *)arg;
    int start = params -> start;
    int end = params -> end;

    // Sort the sublist
    mergeSort(start, end);

    pthread_exit(NULL);
}

int main(){
    // Hardcoded Unsorted Array
    int unsortedArray[SIZE] = {7, 12, 19, 3, 18, 4, 2, 6, 15, 8};

    // Copy the input data to the sortedArray
    for (int i = 0; i < SIZE; i++) {
        sortedArray[i] = unsortedArray[i];
    }

    // Create two sorting threads
    pthread_t sortingThread1, sortingThread2;
    SortParameters params1 = {0, SIZE / 2 - 1};
    SortParameters params2 = {SIZE / 2, SIZE - 1};

    pthread_create(&sortingThread1, NULL, sortThread, (void *)&params1);
    pthread_create(&sortingThread2, NULL, sortThread, (void *)&params2);

    //Sorting
    pthread_join(sortingThread1, NULL);
    pthread_join(sortingThread2, NULL);

    // Merge the two sub-arrays
    merge(0, SIZE / 2 - 1, SIZE - 1);

    // Print out the Unsorted Array
    printf("Unsorted Array: ");
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", unsortedArray[i]);
    }
    printf("\n");

    // Print out the Sorted Array
    printf("Sorted Array: ");
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", sortedArray[i]);
    }
    printf("\n");

    return 0;    
}