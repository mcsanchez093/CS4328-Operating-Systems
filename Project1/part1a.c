/* Author: Michael Wooton
 * CS4328 Operating Systems
 * Project 1 - part1a.c
 *
 * To compile: gcc part1a.c -o part1a -lpthread
 *
 * multi-threaded program that generates the Fibonacci number using Pthreads
*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX_SIZE 45

int fibArr[MAX_SIZE]; //shared by the threads

void *fibonacci(void *param)
{
    int size = *((int*) param);

    int fib1 = 0,
        fib2 = 1;
    long long int fib3;

    fibArr[0] = fib1;
    fibArr[1] = fib2;

    for(int i = 2; i < size; i++)
    {
        fib3 = fib1 + fib2;
        fib1 = fib2;
        fib2 = fib3;
        fibArr[i] = fib3;
    }
    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    int num; //users input
    pthread_t thread; //the thread identifier

    printf("Enter an integer n that is ( 0 < n <= 45 ): ");
    scanf("%d", &num);

    while (num < 0 || num > 45)
    {
        printf("\nERROR: Number must be ( 0 < n <= 45 )\n");
        printf("Enter an integer n that is ( 0 < n <= 45 ): ");
        scanf("%d", &num);
    }

    //Intialize the array
    for (int i = 0; i < num; i++) {
        fibArr[i] = -1;
    }

    pthread_create(&thread, NULL, fibonacci,(void *) &num); //create pthread
    pthread_join(thread, NULL); //wait for the thread to finish

    printf("\nThe Fibonacci Sequence is :\n");
    for (int i = 0; i < num; i++)
    {
        printf("fib(%d)= %d\n", i, fibArr[i]);
    }

    return 0;
}
