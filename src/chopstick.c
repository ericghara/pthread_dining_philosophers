//
// Created by eric on 8/27/23.
//

#include "chopstick.h"

void init_chopstick(Chopstick* chopstick) {
    int s = pthread_spin_init(&chopstick->lock, PTHREAD_PROCESS_PRIVATE);
    if (s != 0) {
        fprintf(stderr, "Unable to initialize chopstick lock.  Err: %d.\n", s);
        exit(s);
    }
}

void destroy_chopstick(Chopstick* chopstick) {
    int s = pthread_spin_destroy(&chopstick->lock);
    if (s != 0) {
        fprintf(stderr, "Unable to destroy chopstick lock. Err: %d\n", s);
        exit(s);
    }
}

void take(Chopstick* chopstick) {
    int s = pthread_spin_lock(&chopstick->lock);
    if (s != 0) {
        fprintf(stderr, "Unable to lock chopstick. Err: %d\n", s);
        exit(-1);
    }
}

void replace(Chopstick* chopstick) {
    int s = pthread_spin_unlock(&chopstick->lock);
    if (s != 0) {
        fprintf(stderr, "Unable to unlock chopstick. Err: %d\n", s);
        exit(-1);
    }
}
