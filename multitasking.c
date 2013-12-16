#include<stdlib.h>
#include <stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <time.h>
#include <pthread.h>
#include <bits/time.h>
#define SIZE_ITER 20000

int my_range(unsigned int min, unsigned int max) {
	return (int) (rand() % (max + 1 - min)) + min;
}
double my_rand() {
	return (double) rand() / (double) RAND_MAX;
}
void* program() {
	char **mas;
	int cur = 0;
	mas = (char **) malloc(SIZE_ITER * sizeof(char*));
	int index;
	for (int i = 0; i < SIZE_ITER; i++) {
		if (my_rand() < 0.3) {
			mas[cur] = (char*) malloc(256 * my_range(1, 4) * sizeof(char));
			cur++;
		}
		if (my_rand() < 0.3) {
			if (cur > 0) {
				cur--;
				free(mas[cur]);
			}
		}
		if (my_rand() < 0.3) {
			if (cur > 0) {
				index = my_range(0, cur - 1);
				mas[index][my_range(0, 255)] = 'A';
			}
		}
	}
	return 0;
}
void threads_program() {
		pthread_t threads[20];
		for(int j = 0; j < 20; j++){
			pthread_create(&threads[j], NULL, program, NULL);
		}
		for(int j = 0;j < 20; j++){
			pthread_join(threads[j], NULL);
		}
}
int main() {
	srand(time(NULL));
	pid_t return_value;
	clock_t start, finish;
	int status;
	double res_time;

	for (int i = 0; i < 5; i++) {
		return_value = fork();
		if (return_value != 0) {
			start = clock();
			threads_program();
			finish = clock();
			res_time = (double) (finish - start) / CLOCKS_PER_SEC;
			printf(
					"\n----------\nThe process id is %d and return value is %d\n",
					getpid(), return_value);
			printf("TIME: %f\n----------\n", res_time);
		}

	}
	return 0;
}
