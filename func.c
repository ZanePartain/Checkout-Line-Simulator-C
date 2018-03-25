/*Zane Partain
10/2/2017
Grocery Line Simulator*/

#include "Header.h"

/*makeNode()
  this function will manually create a QueueNode and populate the Node with their own unique customer number,
  service time, and total time (which accounts for how long the person was in the line in total)*/
QueueNode* makeNode(Data newItem)
{

	QueueNode *pMem = (QueueNode*)malloc(sizeof(QueueNode));

	if (pMem != NULL) // if malloc was successful
	{
		//int memory
		pMem->pNext = NULL;
		pMem->pData = (Data*)malloc(sizeof(Data));

		if (pMem->pData != NULL)
		{
			pMem->pData->customerNumber = newItem.customerNumber;
			pMem->pData->serviceTime = newItem.serviceTime;
			pMem->pData->totalTime = newItem.totalTime;
		}
		else
		{
			printf("Ran out of memory");
		}

	}

	return pMem;

}

// Insert at the end of the queue. 
int enqueue(Queue *pQ, Data newItem)
{
	QueueNode *pMem = makeNode(newItem);
	int success = 0;

	if (pMem != NULL) // memory was successfully allocated
	{
		if (pQ->pHead == NULL) // empty?
		{
			// it's an empty queue!
			// connect both the head and tail to the one new node
			pQ->pHead = pQ->pTail = pMem;
			success = 1;
			

		}
		else // not empty
		{
			pQ->pTail->pNext = pMem;
			pQ->pTail = pMem;
			success = 1;
		}
	}

	return success;
}

/*timePasses()
  This function is used to keep track of the customers time in the lane. The QueueNode's service time will decremeneted when if they are at the head of the queue.
  the QueueNode's totalTime will be incremented as long as they are in the line.  */
void timePasses(Queue *pQ)
{
	QueueNode *pCur = NULL;
	pCur = pQ->pHead;

	if (pCur != NULL)
	{
		//update service time at head of queue
		pCur->pData->serviceTime -= 1; //decrement service time

		if (pCur->pData->serviceTime >= 0)
		{
			//printf("RQ --> ");
			while (pCur != NULL)
			{
				//update total time for all nodes
				pCur->pData->totalTime += 1;
				
				//printf("%d, %d, %d --> ", pCur->pData->customerNumber, pCur->pData->serviceTime, pCur->pData->totalTime);
				pCur = pCur->pNext;
			}
		}
		//printf("\n");
	}

}

//Remove a customer from the queue
int dequeue(Queue* pQ,int lane, int totalTime)
{
	int success = 0;
	Data returnData = { NULL };
	QueueNode* pTemp = NULL;

	pTemp = pQ->pHead;

	if (pTemp != NULL)
	{
		if (pTemp->pData->serviceTime == 0 )
		{
			if (lane == 1)
			{
				printf("LEFT: Express Lane, Time: %d, Customer: %d, Total time in line: %d minutes.\n\n",totalTime, pTemp->pData->customerNumber, pTemp->pData->totalTime);
			}
			if (lane == 2)
			{
				printf("LEFT: Normal Lane, Time: %d,  Customer: %d, Total time in line: %d minutes.\n\n",totalTime, pTemp->pData->customerNumber, pTemp->pData->totalTime);
			}
			if (pQ->pHead == pQ->pTail)
			{
				returnData = *(pQ->pHead->pData); // struct assignment! this memory should not be freed in this function!

				pQ->pHead = pQ->pHead->pNext; // if only 1 node in queue, 
											  // then pQ->pHead should be NULL now!
											  // in this case we need to update the tail pointer as well!
											  // the queue is now empty
				pQ->pTail = NULL; // pQ->pHead should be NULL already

								  // free memory
				free(pTemp->pData);
				free(pTemp);
				success = 1;
			}
			else // more than 1 node in queue
			{
				returnData = *(pQ->pHead->pData); // struct assignment! this memory should not be freed in this function!

				pQ->pHead = pQ->pHead->pNext; // if only 1 node in queue, 
											  // then pQ->pHead should be
											  // free memory
				free(pTemp->pData);
				free(pTemp);
				success = 1;
			}
		}
	}
	return success;
}


void printQueue(Queue pQ)
{
	QueueNode *pCur = pQ.pHead;

	// we will ignore the rules of the queue to print out the items.
	// we will walk through it like a singly-linked list

	printf("REG--> ");
	while (pCur != NULL)
	{
		printf("%d, %d, %d --> ", pCur->pData->customerNumber, pCur->pData->serviceTime, pCur->pData->totalTime);
		pCur = pCur->pNext;
	}


}

int isEmpty(Queue *pQ)
{
	if (pQ->pHead == NULL)
	{
		printf("Lane is empty");
	}
}

int expCustomer()
{
	//generate random service time for express lane customer
	int serviceTime = 0;


	serviceTime = rand() % 5;
	serviceTime += 1;

	return serviceTime;
}

int normCustomer()
{
	//generate random service time for normal lane customer

	int serviceTime = 0;

	serviceTime = rand() % 5;
	serviceTime += 3;

	return serviceTime;

}
