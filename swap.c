#include<stdlib.h>
#include <stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <time.h>
#define SIZE_ITER 6000000
#define SIZE_MEMORY 377487300

int main() {
	srand(time(NULL));
	char *mas = malloc(SIZE_MEMORY * sizeof(char));
	clock_t start, finish;
	if (mas == NULL) {
		printf("ERROR malloc()\n");
		exit(1);
	}
	start = clock();
	for (int i = 0; i < SIZE_ITER; i++) {
		mas[(i + 1) % SIZE_MEMORY] = 'A';
	}
	finish = clock();
	printf("First TIME: %f\n",(double)(finish-start)/CLOCKS_PER_SEC);

	start = clock();
	for (int i = 0; i < SIZE_ITER; i++) {
		mas[rand() % SIZE_MEMORY] = 'A';
	}
	finish = clock();
	printf("Second TIME: %f\n",(double)(finish-start)/CLOCKS_PER_SEC);
	return 0;
}
