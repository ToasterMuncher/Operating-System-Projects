/*
 * Julio Anacleto
 * October 27th, 2025
 * Project 2 - Single thread application of matrix dot product
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 2000

typedef struct {
	int** matrixA;		// First input matrix
	int** matrixB;		// Second input matrix
	int** matrixDot;	// Output matrix
	int startRow;		// Starting row for this thread
	int endRow;		// Ending row for this thread exclusive
	int size;		// Matrix dimension (2000)
} ThreadData;

// Threaded dot product function
void *threadDotProduct(void *arg) {
	ThreadData *data = (ThreadData*) arg;

	// Compute assigned section of matrix
	for (int i = data->startRow; i < data->endRow; i++) {
		for (int j = 0; j < data->size; j++) {
			data->matrixDot[i][j] = 0;
			for (int k = 0; k < data->size; k++) {
				data->matrixDot[i][j] += data->matrixB[k][j] * data->matrixA[i][k];
			}
		}
	}

	return NULL;
}

int main(int argc, char* argv[]) {

	clock_t start, end;
	double cpuTimeUsed;

	int numThreads;

	// Check if user provided number of threads
	if (argc != 2) {
		printf("Usage: %s <number_of_threads>\n", argv[0]);
		return 1;
	}

	// Convert string argument to integer
	numThreads = atoi(argv[1]);

	// Validate input
	if (numThreads <= 0 || numThreads > SIZE) {
		printf("Invalid number of threads. Must be between 1 and %d\n", SIZE);
		return 1;
	}

	printf("Using %d threads\n", numThreads);

        // Allocate memory for matrixs
        int** matrixA = (int**) malloc(SIZE * sizeof(int*));
        int** matrixB = (int**) malloc(SIZE * sizeof(int*));
	int** matrixDot = (int**) malloc(SIZE * sizeof(int*));
	int* dataA = (int*) malloc(SIZE * SIZE * sizeof(int));
	int* dataB = (int*) malloc(SIZE * SIZE * sizeof(int));
	int* dataDot = (int*) malloc(SIZE *  SIZE * sizeof(int));
        for (int i = 0; i < SIZE; i++) {
                matrixA[i] = dataA + (i * SIZE);
                matrixB[i] = dataB + (i * SIZE);
		matrixDot[i] = dataDot + (i * SIZE);
        }

        // Initialize two input  matrixs with values
        int counter = 0;
        for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                        matrixA[i][j] = counter;
                        matrixB[i][j] = counter++;
                }
        }

	// Create thread structures
	pthread_t threads[numThreads];
	ThreadData threadData[numThreads];

	// Begin clock
	start = clock();

	// Divide rows between threads
	int rowsPerThread = SIZE / numThreads;
	for (int i = 0; i < numThreads; i++) {
		threadData[i].matrixA = matrixA;
		threadData[i].matrixB = matrixB;
		threadData[i].matrixDot = matrixDot;
		threadData[i].startRow = i * rowsPerThread;
		threadData[i].endRow = (i == numThreads - 1) ? SIZE : (i + 1) * rowsPerThread;
		threadData[i].size = SIZE;

		// Now that we have the necessary data for a thread, we can now create it and send it to run the operations
		if(pthread_create(&threads[i], NULL, threadDotProduct, &threadData[i]) != 0) {
			perror("Failed to create thread");
			return 1;
		}
	}

	// Wait for all threads to complete
	for (int i = 0; i < numThreads; i++) {
		pthread_join(threads[i], NULL);
	}

	// End Clock
	end = clock();

	// Display time elapsed
	cpuTimeUsed = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Execution time: %f seconds\n", cpuTimeUsed);

        // Display Array (Used for debugging)
        /*
	printf("Matrix multiplication complete\n");
	for (int i = 0; i < SIZE; i++) {
                printf("[ ");
                for (int j = 0; j < SIZE; j++) {
                        printf("%d ", matrixDot[i][j]);
                }
                printf("]\n");
        }
	*/

        // Free allocated memory
	free(matrixA[0]);
	free(matrixB[0]);
	free(matrixDot[0]);
	free(matrixA);
	free(matrixB);
	free(matrixDot);

        return 0;
}

