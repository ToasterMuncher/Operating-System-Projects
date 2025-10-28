/*
 * Julio Anacleto
 * October 27th, 2025
 * Project 2 - Single thread application of matrix dot product
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 2000

void matrixDotProduct(int** matrixDot, int** matrixA, int** matrixB) {
        int indexValue;
        // Matrix dot product
        for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                        int indexValue = 0;
                        for (int k = 0; k < SIZE; k++) {
                                indexValue += matrixA[i][k] * matrixB[k][j];
                        }
                        matrixDot[i][j] = indexValue;
                }
        }
}

int main(void) {

	clock_t start, end;
	double cpuTimeUsed;

	// Two initial dynamic  matrix's used for dot product
	int** matrixA = (int**) malloc(SIZE * sizeof(int*));
	int** matrixB = (int**) malloc(SIZE * sizeof(int*));
	for (int i = 0; i < SIZE; i++) {
		matrixA[i] = (int*) malloc(SIZE * sizeof(int));
		matrixB[i] = (int*) malloc(SIZE * sizeof(int));
	}

	// Initialize both matrixs with values
	int counter = 0;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			matrixA[i][j] = counter;
			matrixB[i][j] = counter++;
		}
	}

	// Matrix that will store dot product
        int** matrixDot = (int**) malloc(SIZE * sizeof(int*));
	for (int i = 0; i < SIZE; i++) {
		matrixDot[i] = (int*) malloc(SIZE * sizeof(int));
	}

	// Call function to alter matrix
	start = clock();
	matrixDotProduct(matrixDot, matrixA, matrixB);
	end = clock();

	// Measure completion time
	cpuTimeUsed = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Execution time: %f seconds\n", cpuTimeUsed);

	// Display Array (Used for debugging with size 4 for ease)
	/*
	for (int i = 0; i < SIZE; i++) {
		printf("[ ");
		for (int j = 0; j < SIZE; j++) {
			printf("%d ", matrixDot[i][j]);
		}
		printf("]\n");
	}
	*/

	// Free allocated memory
	for (int i = 0; i < SIZE; i++) {
		free(matrixA[i]);
		free(matrixB[i]);
		free(matrixDot[i]);
	}
	free(matrixA);
	free(matrixB);
	free(matrixDot);

	return 0;
}
