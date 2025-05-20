#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Semáforos e variáveis globais
sem_t roomEmpty;
pthread_mutex_t mutex;
int dogsInRoom = 0;
int catsInRoom = 0;

// Funções de entrada e saída
void dogWantsToEnter() {
    pthread_mutex_lock(&mutex);
    if (dogsInRoom == 0) {
        sem_wait(&roomEmpty);
    }
    dogsInRoom++;
    printf("Cachorro entrou. Total: %d\n", dogsInRoom);
    pthread_mutex_unlock(&mutex);
}

void dogLeaves() {
    pthread_mutex_lock(&mutex);
    dogsInRoom--;
    printf("Cachorro saiu. Restam: %d\n", dogsInRoom);
    if (dogsInRoom == 0) {
        sem_post(&roomEmpty);
    }
    pthread_mutex_unlock(&mutex);
}

void catWantsToEnter() {
    pthread_mutex_lock(&mutex);
    if (catsInRoom == 0) {
        sem_wait(&roomEmpty);
    }
    catsInRoom++;
    printf("Gato entrou. Total: %d\n", catsInRoom);
    pthread_mutex_unlock(&mutex);
}

void catLeaves() {
    pthread_mutex_lock(&mutex);
    catsInRoom--;
    printf("Gato saiu. Restam: %d\n", catsInRoom);
    if (catsInRoom == 0) {
        sem_post(&roomEmpty);
    }
    pthread_mutex_unlock(&mutex);
}

// Threads simulando entrada e saída
void* dog(void* arg) {
    dogWantsToEnter();
    sleep(1); // simula uso da sala
    dogLeaves();
    return NULL;
}

void* cat(void* arg) {
    catWantsToEnter();
    sleep(1); // simula uso da sala
    catLeaves();
    return NULL;
}

int main() {
    // Inicializações
    sem_init(&roomEmpty, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    pthread_t threads[6];

    // Cria 3 cachorros e 3 gatos
    pthread_create(&threads[0], NULL, dog, NULL);
    pthread_create(&threads[1], NULL, cat, NULL);
    pthread_create(&threads[2], NULL, dog, NULL);
    pthread_create(&threads[3], NULL, cat, NULL);
    pthread_create(&threads[4], NULL, dog, NULL);
    pthread_create(&threads[5], NULL, cat, NULL);

    for (int i = 0; i < 6; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destrói semáforos
    sem_destroy(&roomEmpty);
    pthread_mutex_destroy(&mutex);

    return 0;
}
