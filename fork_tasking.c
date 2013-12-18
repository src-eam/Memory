#include<stdlib.h>
#include <stdio.h>
#include<unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include <pthread.h>

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

int main() {
	pid_t pid;
	for (int i = 0; i < 4; i++) {
		pid = fork();
		if (pid < 0)
			exit(1);
		program();
		wait(0);
	}
	return 0;
}
