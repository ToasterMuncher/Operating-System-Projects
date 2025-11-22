/*
 * Julio Anacleto | Abdullah Almaroof
 * November 19th, 2025
 * Project 3 - Multi thread Scheduler
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NR_PHASES 5

// Basic structure for job information
typedef struct {
	int job_id;
	int nr_phases;
	int current_phase;
	// Phase Types: 1 = CPU ; 2 = IO
	int phaseType_and_duration[2][NR_PHASES];
	int is_completed = 0;
} Job;

// Structure for Queue nodes
typedef struct Node {
	Job j;
	struct Node* next;
} Node;

// Structure for Queue using nodes
typedef struct {
	Node* front;
	Node* rear;
	int size;
} Queue;

// Gloabl Variable
int jobId;

Queue* createQueue() {
	Queue* q = (Queue*) malloc(sizeof(Queue));
	queue->front = NULL;
	queue->rear = NULL;
	queue->size = 0;
	return queue;
}

// Unsure of correct operation, need to create test block for verification
void enqueue(Queue* q, int data) {
	// Create and allocate space for Node structure
	Node* newNode = (Node*) malloc(sizeof(Node));

	// Initialize Job structure variable
	Job* newJob = newNode->j;
	newJob->job_id = jobID;
	newJob->nr_phases = NR_PHASES;
	newJob->current_phase = 0;
	newJob->phaseType_and_duration = (int*) malloc(2 * sizeof(int*));
	for (int i = 0; i < 2; i++) {
		newJob->phaseType_and_duration[i] = malloc(NR_PHASES * sizeof(int));
	}

	// Position
	if (q->rear == null) {
		q->rear = newNode;
		q->front = newNode;
		q->size++;
	}
	else {
		newNode->next = q->rear;
		q->rear = newNode;
		q->size++;
	}
}
