/* Author: Michael Wooton
 * CS4328 Operating Systems
 * Project 1 - part2a.c
 *
 * Compile: gcc part2a.c -o part2a -lpthread
 *
 * This program implements matrix multiplicatin using pthreads
 * Matrix A * Matrix B = Matrix C
*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define M 3
#define K 2
#define N 3
#define NUM_THREADS M*N

int A [M][K] = {{1,4}, {2,5}, {3,6}};
int B [K][N] = {{8,7,6}, {5,4,3}};
int C [M][N];

struct thread_args
{
    int row;
    int col;
};

void *matrixMul (void *param)
{
    struct thread_args *data = param;
    int i;

    for (i = 0; i < K; i++)
    {
        C[data->row][data->col]  += A[data->row][i] * B[i][data->col];
    }
    pthread_exit(0);
}

int main (int argc, char *argv[])
{
    int i, j, counter = 0;
    pthread_t threads[NUM_THREADS];

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            struct thread_args *data = (struct thread_args *)
                                        malloc (sizeof (struct thread_args));
            data->row = i;
            data->col = j;

            pthread_create(&threads[counter], NULL, matrixMul, data);
            counter++;
        }
    }

    //Wait for threads to complete
    for(i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("Matrix A\n");
    for (i = 0; i < M; i++) {
        for (j = 0; j < K; j++) {
            printf("%d   ", A[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrix B\n");
    for (i = 0; i < K; i++) {
        for (j = 0; j < N; j++) {
            printf("%d   ", B[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrix A * B = C\n");
    printf("\nMatrix C\n");
    for (i = 0; i < M; i++) {
        for(j = 0; j < N; j++) {
            printf("%d   ", C[i][j]);
	}
	printf("\n");
    }

    return 0;
}
