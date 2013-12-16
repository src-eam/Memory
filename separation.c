#include<stdlib.h>
#include <stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <time.h>
#include <pthread.h>

#define N 40
#define SIZE_ITER 2000000
volatile int first_counters[N];
volatile int second_counters[N][128];

void* first_program(void* th_id) {
	int id = *((int*) (&th_id));
	for (int i = 0; i < SIZE_ITER; i++) {
		first_counters[id]++;
	}
	return 0;
}

void* second_program(void* th_id) {
	int id = *((int*) (&th_id));
	for (int i = 0; i < SIZE_ITER; i++) {
		second_counters[id][0]++;
	}
	return 0;
}
void first_threads() {
	pthread_t threads[N];
	for (int j = 0; j < N; j++) {
		pthread_create(&threads[j], NULL, first_program,(void*) j);
	}
	for (int j = 0; j < N; j++) {
		pthread_join(threads[j], NULL);
	}
}

void second_threads() {
	pthread_t threads[N];
	for (int j = 0; j < N; j++) {
		pthread_create(&threads[j], NULL, second_program,(void*) j);
	}
	for (int j = 0; j < N; j++) {
		pthread_join(threads[j], NULL);
	}
}

int main() {
	clock_t start, finish;
	start = clock();
	first_threads();
	finish = clock();
	printf("First TIME: %f\n",(double)(finish-start)/CLOCKS_PER_SEC);

	start = clock();
	second_threads();
	finish = clock();
	printf("Second TIME: %f\n",(double)(finish-start)/CLOCKS_PER_SEC);

	return 0;
}
