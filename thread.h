#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int MAXTHREAD = 50;


//funcion que imprime hola + identificador
void* hola(void* arg) {
	int id;
	id=pthread_self();
	printf("Hola %d\n",id);
	return 0;
}

int main(int argc, char** argv) {
	int i;
	pthread_t ptarray[MAXTHREAD];
	int count = 0;

//creacion de hilos
for (i = 0; i < MAXTHREAD; i++) {
		pthread_create(&ptarray[i], NULL, hola, NULL);
	}


//se espera a que termine cada hilo
for (i = 0; i < MAXTHREAD; i++) {
		pthread_join(ptarray[i],NULL);
	}
}
