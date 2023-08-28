//
// Created by eric on 8/27/23.
//

#pragma once

#include "chopstick.h"


typedef struct {
    unsigned long id;
    unsigned int bites_taken;
    unsigned int max_bites;
    Chopstick* left;
    Chopstick* right;
} Philosopher;

void init_philosopher(Philosopher* philosopher, unsigned long id, unsigned int max_bites, Chopstick* left, Chopstick* right);

void take_bite(Philosopher* philosopher);

// arg should be a pointer to a philosopher
void* eat(void* arg);
