/*Zane Partain
10/2/2017
Grocery Line Simulator*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct data
{
	int customerNumber; // Unique identifier; starts at 1; after 24 hours should be reset to 1
	int serviceTime; // Random time; varies between express and normal lanes; units in minutes
	int totalTime;//totalTime = serviceTime + sum of serviceTimes of customers in line before this customer; units in minutes
} Data; // This memory needs to be allocated on the heap!

typedef struct queueNode
{
	Data *pData;// The memory for Data will need to be allocated on the heap as well!

	struct queueNode *pNext;
} QueueNode;

typedef struct queue
{
	QueueNode *pHead;
	QueueNode *pTail;
} Queue; // this is the queue container


//make a node for the queue
QueueNode* makeNode(Data newItem);

//insert queuenode at end of queue
int enqueue(Queue *pQ, Data newItem);

//update each individual nodes serviceTime and totalTime 
void timePasses(Queue *pQ);

//generate a random service time for express lane customer
int expCustomer();

//generate a random service time for normal lane customer
int normCustomer();

//free node from queue is service time is 0
int dequeue(Queue* pQ, int lane, int totalTime);

//display the current queue
void printQueue(Queue pQ);

//check if queue is empty
int isEmpty(Queue *pQ);
