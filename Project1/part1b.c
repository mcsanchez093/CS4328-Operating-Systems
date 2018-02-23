/* Author: Michael Wooton
 * CS4328 Operating Systems
 * Project 1 - part1b.c
 *
 * multi-threaded program that generates the Fibonacci number using Win32 threads
*/

#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#define MAX_SIZE 45

DWORD fibArr[MAX_SIZE]; //shared array by threads

DWORD WINAPI fibonacci(LPVOID lpParam)
{
    int size = *((int*) lpParam);

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
}

int main(int argc, TCHAR *argv[])
{
    int num; //user input

    DWORD ThreadId;
    HANDLE childThread;

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

    // Start the child process.
    childThread = CreateThread(
        NULL,       // Default Security
        0,          // Default Stack size
        fibonacci,  // thread function
        &num,       // function parameter
        0,          // Default flags
        &ThreadId); // thread identifier

    // Wait until child process exits
    WaitForSingleObject(childThread, INFINITE);

    // Close thread handle
    CloseHandle(childThread);

    printf("\nThe Fibonacci Sequence is :\n");
    for (int i = 0; i < num; i++)
    {
        printf("fib(%d)= %d\n", i, fibArr[i]);
    }

    return 0;
}
