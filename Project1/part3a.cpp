/* Author: Michael Wooton
 * CS4328 Operating Systems
 * Project 1 - part3a.cpp
 *
 * Compile: g++ part3a.cpp -o part3a -fopenmp
 *
 * Program to count how many 99's in a given array using OpenMP threads. Records the execution time
 * of the serial code and the parallel code when using 2, 4, and 8 threads to show the speedup..
*/

#include <omp.h>
#include <stdlib.h>
#include <ctime>
#include <stdio.h>

using namespace std;

int const SIZE = 500000000; 
int *myArray = new int[SIZE];

void parallelCode (int threads)
{
    int count = 0, i;
    double start_time, end_time;

    start_time = omp_get_wtime();

    #pragma omp parallel for default(none) shared(myArray) private(i) reduction(+:count) num_threads(threads)
    for (i = 0; i < SIZE; i++) {
        if (myArray[i] == 99)
            count ++;
    }

    end_time = omp_get_wtime();

    printf("The parallel code for %d threads, indicates that there are %d 99s in the array.\n", threads, count);
    printf("The parallel code used %f seconds to complete the execution.\n\n", end_time - start_time);
}

int main()
{
    int count = 0, i;

    double start_time, end_time;

    //initialize random number generator
    srand((unsigned)time(NULL));

    // Initialize the array using random numbers
    for (i = 0; i < SIZE; i++)
        myArray[i] = rand() % 100;

    //Serial Code
    start_time = omp_get_wtime();

    for (i = 0; i < SIZE; i++) {
        if (myArray[i] == 99)
            count ++;
    }

    end_time = omp_get_wtime();

    printf("\nThe serial code indicates that there are %d 99s in the array.\n", count);
    printf("The serial code used %f seconds to complete the execution.\n\n", end_time - start_time);

    //Parallel Code 
    parallelCode(2); // running 2 threads
    parallelCode(4); // running 4 threads
    parallelCode(8); // running 8 threads

    delete[] myArray;

    return 0;
}
