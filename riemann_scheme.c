#include <stdio.h>
#include <pthread.h>
#include <math.h>
#define MAXRECT 1000000
#define MAXTHREAD 10
#define BASE 0.0
#define LIMIT 1.0

double length = LIMIT - BASE; // La longitud en el eje 'x'
double numRectxThread = (double)(MAXRECT/MAXTHREAD); // Cuantos hilos/rectangulo
double base_length = 0; // Variable que tiene el ancho de cada rectangulo
double sumTotal = 0; // Variable que tendra la suma total
double partialSums[MAXTHREAD]; // Variable que tien la suma parcial de c/hilo

// Funcion a la que se le calculara la integral, x^2
double function(double x) {
	return x * x; 
}
void* calcular(void *arg) {
	
	int id = (int)arg;
      
	int loslimit=(id*numRectxThread)/(MAXRECT);
	
	partialSums[id]=0;
	
	int i;
	int val;
	int other;
	for (i= loslimit*10; i<loslimit +numRectxThread ; i++){
	partialSums[id]+= (function(i)*base_length/10000000000);
	}
	printf("sum: %lf\n", partialSums[id]);
	pthread_exit(NULL);
}

int main(int argc, char** argv) {
	pthread_t identi[MAXTHREAD];
	long identiH[MAXTHREAD];
	long taskids[MAXTHREAD];
	base_length = length/MAXRECT; // esta variable contiene el ancho de
				      // cada base de cada rectangulo
	printf("base length: %lf numRectxThread: %lf\n",base_length, numRectxThread);

	// Creacion de los hilos que calcularan el area bajo la curva
	for (int i = 0; i < MAXTHREAD; i++) {
		taskids[i] =(long) i;
		identiH[i]=pthread_create(&identi[i], NULL, calcular, (void*)taskids[i]);
	}
	// Ciclo donde se espera el resultado de cada hilo
	for (int i = 0; i < MAXTHREAD; i++) {
		pthread_join(identi[i], NULL);
		sumTotal += partialSums[i];
	}
	printf("Suma total %lf\n",sumTotal); 
	pthread_exit(NULL);
}
