#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "vet_clinic.h"

#define NUM_DOGS 3
#define NUM_CATS 3

// Declaração dos semáforos e mutex (externos)
extern sem_t roomEmpty;
extern pthread_mutex_t mutex;

int main() {
    pthread_t dogs[NUM_DOGS], cats[NUM_CATS];

    sem_init(&roomEmpty, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    // Cria os cães primeiro
    for (int i = 0; i < NUM_DOGS; i++) {
        pthread_create(&dogs[i], NULL, dog, NULL);
    }

    sleep(5); // espera os cães saírem

    // Depois os gatos
    for (int i = 0; i < NUM_CATS; i++) {
        pthread_create(&cats[i], NULL, cat, NULL);
    }

    for (int i = 0; i < NUM_DOGS; i++) {
        pthread_join(dogs[i], NULL);
    }
    for (int i = 0; i < NUM_CATS; i++) {
        pthread_join(cats[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&roomEmpty);

    return 0;
}
