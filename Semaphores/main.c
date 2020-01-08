#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include "fifo.h"
#define up(n) sem_post(n)
#define down(n) sem_wait(n)

sem_t A1, A2, B1, B2;
sem_t Mutex;

void initSems() {
	sem_init(&A1, 0, 10);
	sem_init(&A2, 0, 0);
	sem_init(&B1, 0, 0);
	sem_init(&B2, 0, 0);
	sem_init(&Mutex, 0, 1);
}

void destroySems() {
	sem_destroy(&A1);
	sem_destroy(&A2);
	sem_destroy(&B1);
	sem_destroy(&B2);
	sem_destroy(&Mutex);
}

FIFO* BufEven;
FIFO* BufOdd;
int semval;

void* procA1() {
	int num = 0;
	while(true) {
		down(&A1);
		down(&Mutex);
		put(BufEven, num);
		printf("Zapisano %d ", num);
		printf("BufOdd size: %d BufEven size: %d\n", size(BufOdd), size(BufEven));
		printf("Stan kolejki bufOdd: ");
		printQueue(BufOdd);
		printf("Stan kolejki BufEven: ");
		printQueue(BufEven);
		num = (num+2)%100;
		if(size(BufEven) >= 3)
			up(&B1);
		up(&Mutex);
		up(&A2);

		sem_getvalue(&A1, &semval);
		printf("SEM A1: %d\n", semval);
		sem_getvalue(&A2, &semval);
		printf("SEM A2: %d\n", semval);
		sem_getvalue(&B1, &semval);
		printf("SEM B1: %d\n", semval);
		sem_getvalue(&B2, &semval);
		printf("SEM B2: %d\n", semval);
		sem_getvalue(&Mutex, &semval);
		printf("SEM Mutex: %d\n", semval);
	}
}

void* procA2() {
	int num = 1;
	while(true) {
		down(&A2);
		down(&Mutex);
		put(BufOdd, num);
		printf("Zapisano %d ", num);
		printf("BufOdd size: %d BufEven size: %d\n", size(BufOdd), size(BufEven));
		printf("Stan kolejki bufOdd: ");
		printQueue(BufOdd);
		printf("Stan kolejki BufEven: ");
		printQueue(BufEven);
		num = (num+2)%100;
		if(size(BufOdd) >= 3)
			up(&B2);
		up(&Mutex);

		sem_getvalue(&A1, &semval);
		printf("SEM A1: %d\n", semval);
		sem_getvalue(&A2, &semval);
		printf("SEM A2: %d\n", semval);
		sem_getvalue(&B1, &semval);
		printf("SEM B1: %d\n", semval);
		sem_getvalue(&B2, &semval);
		printf("SEM B2: %d\n", semval);
		sem_getvalue(&Mutex, &semval);
		printf("SEM Mutex: %d\n", semval);
	}
}

void* procB1() {
	while(true) {
		down(&B1);
		down(&Mutex);
		printf("Odczytano %d\n", get(BufEven));
		printf("BufOdd size: %d BufEven size: %d\n", size(BufOdd), size(BufEven));
		printf("Stan kolejki bufOdd: ");
		printQueue(BufOdd);
		printf("Stan kolejki BufEven: ");
		printQueue(BufEven);
		if(size(BufEven) < 10)
			up(&A1);
		up(&Mutex);
		down(&A2);

		sem_getvalue(&A1, &semval);
		printf("SEM A1: %d\n", semval);
		sem_getvalue(&A2, &semval);
		printf("SEM A2: %d\n", semval);
		sem_getvalue(&B1, &semval);
		printf("SEM B1: %d\n", semval);
		sem_getvalue(&B2, &semval);
		printf("SEM B2: %d\n", semval);
		sem_getvalue(&Mutex, &semval);
		printf("SEM Mutex: %d\n", semval);
	}
}

void* procB2() {
	while(true) {
		down(&B2);
		down(&Mutex);
		printf("Odczytano %d\n", get(BufOdd));
		printf("BufOdd size: %d BufEven size: %d\n", size(BufOdd), size(BufEven));
		printf("Stan kolejki bufOdd: ");
		printQueue(BufOdd);
		printf("Stan kolejki BufEven: ");
		printQueue(BufEven);
		up(&Mutex);
		up(&A2);

		sem_getvalue(&A1, &semval);
		printf("SEM A1: %d\n", semval);
		sem_getvalue(&A2, &semval);
		printf("SEM A2: %d\n", semval);
		sem_getvalue(&B1, &semval);
		printf("SEM B1: %d\n", semval);
		sem_getvalue(&B2, &semval);
		printf("SEM B2: %d\n", semval);
		sem_getvalue(&Mutex, &semval);
		printf("SEM Mutex: %d\n", semval);
	}
}

int main(int argc, char* argv[]) {
	if(argc != 5) {
		puts("Syntax: main [num_of_A1] [num_of_A2] [num_of_B1] [num_of_B2]");
		return 1;
	}

	int numofA1 = atoi(argv[1]), numofA2 = atoi(argv[2]),
		numofB1 = atoi(argv[3]), numofB2 = atoi(argv[4]);

	if(numofA1 <= 0 || numofA2 <= 0 || numofB1 <= 0 || numofB2 <= 0) {
		puts("Error: expected positive integers.");
		return 1;
	}

	BufEven = initFIFO();
	BufOdd = initFIFO();
	initSems();

	pthread_t threads[numofA1+numofA2+numofB1+numofB2];

	for(int i = 0; i < numofA1; ++i)
		pthread_create(&threads[i], NULL, &procA1, NULL);
	for(int i = numofA1; i < numofA1+numofA2; ++i)
		pthread_create(&threads[i], NULL, &procA2, NULL);
	for(int i = numofA1+numofA2; i < numofA1+numofA2+numofB1; ++i)
		pthread_create(&threads[i], NULL, &procB1, NULL);
	for(int i = numofA1+numofA2+numofB1; i < numofA1+numofA2+numofB1+numofB2; ++i)
		pthread_create(&threads[i], NULL, &procB2, NULL);

	for(int i = 0; i < numofA1+numofA2+numofB1+numofB2; ++i)
		pthread_join(threads[i], NULL);

	destroySems();
	del(BufEven);
	del(BufOdd);

	return 0;
}
