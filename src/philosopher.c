//
// Created by eric on 8/28/23.
//

#include "philosopher.h"

void init_philosopher(Philosopher* philosopher, unsigned long id, unsigned int max_bites, Chopstick* left, Chopstick* right) {
    philosopher->id = id;
    philosopher->max_bites = max_bites;
    philosopher->bites_taken = 0;
    philosopher->left = left;
    philosopher->right = right;
}

void take_bite(Philosopher* philosopher) {
    Chopstick* first;
    Chopstick* second;
    if (philosopher->id&1) {
        first = philosopher->left;
        second = philosopher->right;
    }
    else {
        first = philosopher->right;
        second = philosopher->left;
    }
    take(first);
    take(second);
    replace(first);
    replace(second);
    philosopher->bites_taken++;
}

// arg should be a pointer to a philosopher
void* eat(void* arg) {
    Philosopher* philosopher = (Philosopher*) arg;
    while (philosopher->bites_taken < philosopher->max_bites) {
        take_bite(philosopher);
    }
    return NULL;
}
