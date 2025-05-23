#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include "vet_clinic.h"

// Semáforos e variáveis globais
sem_t roomEmpty;
pthread_mutex_t mutex;
int dogsInRoom = 0;
int catsInRoom = 0;

// Funções de entrada e saída

void dogWantsToEnter() {
    pthread_mutex_lock(&mutex);
    if (dogsInRoom == 0)
        sem_wait(&roomEmpty);
    dogsInRoom++;
    printf("Cachorro entrou. Total: %d\n", dogsInRoom);
    pthread_mutex_unlock(&mutex);
}

void dogWantsToLeave() {
    pthread_mutex_lock(&mutex);
    dogsInRoom--;
    printf("Cachorro saiu. Restam: %d\n", dogsInRoom);
    if (dogsInRoom == 0)
        sem_post(&roomEmpty);
    pthread_mutex_unlock(&mutex);
}

void catWantsToEnter() {
    pthread_mutex_lock(&mutex);
    if (catsInRoom == 0)
        sem_wait(&roomEmpty);
    catsInRoom++;
    printf("Gato entrou. Total: %d\n", catsInRoom);
    pthread_mutex_unlock(&mutex);
}

void catWantsToLeave() {
    pthread_mutex_lock(&mutex);
    catsInRoom--;
    printf("Gato saiu. Restam: %d\n", catsInRoom);
    if (catsInRoom == 0)
        sem_post(&roomEmpty);
    pthread_mutex_unlock(&mutex);
}

// Funções de thread

void* dog(void* arg) {
    dogWantsToEnter();
    sleep(1); // simula tempo de permanência
    dogWantsToLeave();
    return NULL;
}

void* cat(void* arg) {
    catWantsToEnter();
    sleep(1); // simula tempo de permanência
    catWantsToLeave();
    return NULL;
}
