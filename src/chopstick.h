//
// Created by eric on 8/27/23.
//

#pragma once

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    pthread_spinlock_t lock;
} Chopstick;

void init_chopstick(Chopstick* chopstick);

void destroy_chopstick(Chopstick* chopstick);

void take(Chopstick* chopstick);

void replace(Chopstick* chopstick);
