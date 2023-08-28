//
// Created by eric on 8/27/23.
//

#pragma once
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Chopstick {
    pthread_mutex_t lock;
} Chopstick;

void init_chopstick(Chopstick* chopstick);

void destroy_chopstick(Chopstick* chopstick) {
    int s = pthread_mutex_destroy(&chopstick->lock);
    if (s != 0) {
        fprintf(stderr, "Unable to destroy chopstick lock. Err: %d\n", s);
        exit(s);
    }
}

void take(Chopstick* chopstick) {
    int s = pthread_mutex_lock(&chopstick->lock);
    if (s != 0) {
        fprintf(stderr, "Unable to lock chopstick. Err: %d\n", s);
        exit(-1);
    }
}

void replace(Chopstick* chopstick) {
    int s = pthread_mutex_unlock(&chopstick->lock);
    if (s != 0) {
        fprintf(stderr, "Unable to unlock chopstick. Err: %d\n", s);
        exit(-1);
    }
}
