#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "philosopher.h"
#include "chopstick.h"

typedef struct timespec timespec;

unsigned long num_philosophers;
unsigned long max_bites;
timespec start_time;
Philosopher* pPhilosophers;
Chopstick* pChopsticks;
pthread_t* pPthreads;


void setup() {
    pPhilosophers = malloc(num_philosophers * sizeof(Philosopher));
    pChopsticks = malloc(num_philosophers * sizeof(Chopstick));
    pPthreads = malloc(num_philosophers*sizeof(pthread_t));
    for (unsigned long i = 0; i < num_philosophers; i++) {
        init_chopstick(&pChopsticks[i]);
        unsigned long prev_i = (i == 0 ? num_philosophers-1 : i-1);
        init_philosopher(&pPhilosophers[i], i, max_bites, &pChopsticks[prev_i], &pChopsticks[i]);
    }
}

void print_time_diff() {
    timespec end_time;
    int s = clock_gettime(CLOCK_MONOTONIC,&end_time);
    if (s != 0) {
        fprintf(stderr, "Unable to get start time.  Error: %d\n", s);
        exit(s);
    }
    end_time.tv_sec -= start_time.tv_sec;
    end_time.tv_nsec -= start_time.tv_nsec;
    double secs = (double) end_time.tv_sec;
    secs += (double) end_time.tv_nsec / 10000000000;
    printf("Time Elapsed: %f\n", secs);
}

void run() {
    // start timing
    int s = clock_gettime(CLOCK_MONOTONIC,&start_time);
    if (s != 0) {
        fprintf(stderr, "Unable to get start time.  Error: %d\n", s);
        exit(s);
    }
    for (unsigned long i = 0; i < num_philosophers; i++) {
        s = pthread_create(&pPthreads[i], NULL, eat,  &pPhilosophers[i]);
        if (s != 0) {
            fprintf(stderr, "Unable to create philosopher: %lu, err: %d\n", i, s);
            exit(s);
        }
    }
    for (unsigned long i = 0; i < num_philosophers; i++) {
        s = pthread_join(pPthreads[i], NULL);
        if (s != 0) {
            fprintf(stderr, "Unable to join thread for philosopher %lu.\n", i);
            exit(s);
        }
        printf("Philosopher %lu took %u bites.\n", i, pPhilosophers[i].bites_taken);
    }
    print_time_diff();
}

void teardown() {
    for (unsigned long i = 0; i < num_philosophers; i++) {
        destroy_chopstick(&pChopsticks[i]);
    }
    free(pChopsticks);
    free(pPhilosophers);
    free(pPthreads);
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: provide number of philosophers to dine. And number of bites each should take.\n");
        exit(1);
    }
    long tmp_num = strtol(argv[1], NULL, 10);
    if (tmp_num <= 0) {
        printf("Provide a positive number of philosophers.\n");
        exit(1);
    }
    num_philosophers = (unsigned long) tmp_num;
    tmp_num = strtol(argv[2], NULL, 10);
    if (tmp_num < 0) {
        printf("Provide a number of bites >= 0.\n");
        exit(1);
    }
    max_bites = tmp_num;
    setup();
    run();
    teardown();
}
