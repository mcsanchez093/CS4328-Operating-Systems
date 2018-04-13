/* Author: Michael Wooton
 * CS4328 Operating Systems
 * Project 2 - part1.c
 *
 * Compile: gcc part1.c -o part1 -lpthread
 *
 * Producer/Consumer Problem with bounded buffer. Semaphore-based solution
 * using pthreads and three semaphores: full, empty and mutex.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];

pthread_mutex_t mutex;
sem_t full;
sem_t empty;

int next_in = 0;
int next_out = 0;

// Producer threads
void *insert_item (void *param)
{
	int index = *((int*) param);
	int random;
	srand(time(NULL));

    while (1)
    {
    	random = rand() % 1000;

    	sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[next_in] = random;
        printf("Producer %d produced: %d\n", index, buffer[next_in]);
        next_in = (next_in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

// Consumer threads
void *remove_item (void *param)
{
	int index = *((int*) param);

	while (1)
	{
		sem_wait(&full);
        pthread_mutex_lock(&mutex);
        
        int item = buffer[next_out];
        printf("\tConsumer %d consumed: %d\n", index, buffer[next_out]);
        next_out = (next_out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
	}
}

int main(int argc, char *argv[])
{
	int time_to_sleep, num_prod, num_con, num_threads, num, thread_num;

	if (argc != 4) 
	{
		printf("ERROR: Not enough parameters\n");
		printf("Usage: ./part1 sleep_time -> number_of_producers -> number_of_consumers\n");
        exit(1);
    }

    time_to_sleep = atoi(argv[1]); // Time to sleep before terminating program
    num_prod = atoi(argv[2]); // number of producer threads
    num_con = atoi(argv[3]); // number of consumer threads

    pthread_mutex_init(&mutex, NULL);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFFER_SIZE);

    num_threads = num_prod + num_con;
    pthread_t threads[num_threads];

    // Create Producer threads
    for (int i = 0; i < num_prod; i++)
    {
    	num = i;
    	thread_num = i;
    	pthread_create(&threads[num], NULL, insert_item, (void *) &thread_num);
    }

    // Create Consumer threads
    for (int i = num_prod; i < num_threads; i++)
    {
    	num = i;
    	thread_num = i - num_prod;
    	pthread_create(&threads[num], NULL, remove_item, (void *) &thread_num);
    }
    
    // Sleep before terminating the program
    sleep(time_to_sleep);

    // Cancel all threads running
    for (int i = 0; i < num_threads; i++)
    {
    	pthread_cancel(threads[i]);
    }

    return 0;
}