/* Author: Michael Wooton
 * CS4328 Operating Systems
 * Project 1 - part3b.cpp
 *
 * Compile: g++ part3b.cpp -o part3b -lpthread -fopenmp
 *
 * Program to count how many 99's in a given array using pthreads. Records the execution time
 * of the serial code and the parallel code when using 2, 4, and 8 threads to show the speedup.
*/

#include <stdlib.h>
#include <ctime>
#include <stdio.h>
#include <pthread.h>
#include <omp.h>

using namespace std;

int const SIZE = 500000000; 
int *myArray = new int[SIZE];

struct thread_args
{
	int num;
	int start;
	int end;
};

void *count99s(void *param)
{
    struct thread_args *data = (thread_args*) param;

    for (int i = data->start; i < data->end; i++)
    {
    	if (myArray[i] == 99)
            data->num++;
    }

    pthread_exit(0);

}

void parallelCode(int threads)
{
    pthread_t workers[threads];
    struct thread_args ta[threads];

    double start_time, end_time;
    
    int counter = 0, count = 0;
    int workSize = SIZE/threads;
    
    start_time = omp_get_wtime();

    for (int i = 0; i < threads; i++)
    {
        struct thread_args *data = &ta[i];
        data->num = 0;
        data->start = i * workSize;
        data->end = (i + 1) * workSize;
    	pthread_create(&workers[counter], NULL, count99s, (void*) data);
    	counter++;
    }

    for (int i = 0; i < threads; i++)
    {
    	pthread_join(workers[i], NULL);
    	count += ta[i].num;
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

    //Parallel Code using pthreads
    parallelCode(2);
    parallelCode(4);
    parallelCode(8);

    delete[] myArray;

    return 0;
}