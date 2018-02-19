#include <stdio.h>
#include <pthread.h>
#include <cstdlib>

#define MAX_SIZE 45

int fib_arr[MAX_SIZE]; //shared by the threads

void *fibonacci(void *param)
{
    int size = *((int*) param);

    int fib1 = 0, fib2 = 1;
    long long int fib3;

    for(int i = 0; i < size; i++)
    {
        fib3 = fib1 + fib2;
        fib1 = fib2;
        fib2 = fib3;
        fib_arr[i] = fib3;
    }
    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    int num;
    pthread_t thread; //the thread identifier

    printf("Enter an integer n that is ( 0 < n <= 45 ): ");
    scanf("%d", &num);

    while (num < 0 || num > 45)
    {
        printf("\nERROR: Number must be ( 0 < n <= 45 )\n");
        printf("Enter an integer n that is ( 0 < n <= 45 ): ");
        scanf("%d", &num);
    }

    pthread_create(&thread, NULL, fibonacci,(void *) &num); //create pthread
    pthread_join(thread, NULL); //wait for the thread to finish

    printf("\nThe Fibonacci Sequence is : ");
    for (int i = 0; i < num; i++)
    {
        printf("%d ", fib_arr[i]);
    }

    return 0;
}
