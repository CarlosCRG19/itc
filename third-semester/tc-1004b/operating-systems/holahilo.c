#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 100
pthread_mutex_t lockSaldo = PTHREAD_MUTEX_INITIALIZER;

int saldo;

void *suma100(void *args){
    int saldoLocal;
    pthread_mutex_lock(&lockSaldo);
    saldoLocal = saldo;
    saldoLocal += 100;
    saldo = saldoLocal;
    printf("Hola, desde hilo \n");
    pthread_mutex_unlock(&lockSaldo);
    pthread_exit(NULL);
}

int main() {

    pthread_t threads[NUM_THREADS];
    saldo = 0;

    for (int i = 0; i < NUM_THREADS; i++){
        pthread_create(&threads[i], NULL, suma100, NULL);
    }
    for (int i = 0; i < NUM_THREADS; i++){
        pthread_join(threads[i], NULL);
    }

    printf("Saldo final: %d \n", saldo);
    pthread_exit(NULL);

    return 0;
}