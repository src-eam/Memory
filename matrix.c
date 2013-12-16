#include<stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <pthread.h>

#define N 1024
#define OFSET (N/4)

//для первого типа матриц
int matrixA[N][N];
int matrixB[N][N];
int matrixR[N][N];

//для второго типа матриц
#define M 16 //размер блока
int matrixA_2[N / M][N / M][M][M];
int matrixB_2[N / M][N / M][M][M];
int matrixR_2[N / M][N / M][M][M];

void init_matrix(int m[][N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			m[i][j] = 1;
		}
	}
}
void* mul_matrix(void* _beg) {
	int i_ndex = *((int*) (&_beg));
	int count = OFSET;
	for (; count > 0; i_ndex++, count--) {
		for (int j_ndex = 0; j_ndex < N; j_ndex++) {
			matrixR[i_ndex][j_ndex] = 0;
			for (int k = 0; k < N; k++) {
				matrixR[i_ndex][j_ndex] += (matrixA[i_ndex][k]
						* matrixB[k][j_ndex]);
			}
		}
	}
	return 0;
}

void print_matrix(int m[][N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", m[i][j]);
		}
		printf("\n");
	}

}

void threads_matrix(void* (*f)(void *)) {
	int size = 4;
	pthread_t threads[size];
	int count = OFSET;
	int _bb = 0;
	for (int c = 0; c < size; c++) {
		pthread_create(&threads[c], NULL, f, (void*) _bb);
		_bb += count;
	}
	for (int j = 0; j < size; j++) {
		pthread_join(threads[j], NULL);
	}
}

void init_matrix_2(int m[N / M][N / M][M][M]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			m[i / M][j / M][i % M][j % M] = 1;
		}
	}
}
void* mul_matrix_2(void* _beg) {
	int i_ndex = *((int*) (&_beg));
	int count = OFSET;
	for (; count > 0; i_ndex++, count--) {
		for (int j_ndex = 0; j_ndex < N; j_ndex++) {
			matrixR_2[i_ndex / M][j_ndex / M][i_ndex % M][i_ndex % M] = 0;
			for (int k = 0; k < N; k++) {
				matrixR_2[i_ndex / M][j_ndex / M][i_ndex % M][i_ndex % M] +=
						(matrixA_2[i_ndex / M][k / M][i_ndex % M][k % M]
								* matrixB_2[k / M][j_ndex / M][k % M][j_ndex % M]);
			}
		}
	}
	return 0;
}

int main() {
	clock_t start, finish;

	init_matrix(matrixA);
	init_matrix(matrixB);

	start = clock();
	threads_matrix(mul_matrix);
	finish = clock();

	printf("First TIME: %f\n", (double) (finish - start) / CLOCKS_PER_SEC);


	init_matrix_2(matrixA_2);
	init_matrix_2(matrixB_2);

	start = clock();
	threads_matrix(mul_matrix_2);
	finish = clock();
	printf("Second TIME: %f\n", (double) (finish - start) / CLOCKS_PER_SEC);
	return 0;
}
