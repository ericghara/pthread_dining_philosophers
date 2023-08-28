//
// Created by eric on 8/27/23.
//

#include "chopstick.h"

void init_chopstick(Chopstick* chopstick) {
    int s = pthread_mutex_init(&chopstick->lock, NULL);
    if (s != 0) {
        fprintf(stderr, "Unable to initialize chopstick lock.  Err: %d.\n", s);
        exit(s);
    }
}