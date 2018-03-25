/*Zane Partain
10/2/2017
Grocery Line Simulator*/


#include "Header.h"

int main(void)
{
	Data exp, norm; //express or normal lane customer.
	Queue expressLane; // the lanes
	Queue normalLane;
	int expCount = 0, normCount = 0, totalTime = 0, expArrival = 0, normArrival = 0, mins = 0, think = 0;
	int newExpCustomer = 0, newNormCustomer = 0, expHasArrived = 0, normHasArrived = 0;
	srand((unsigned)time(NULL));

	expressLane.pHead = NULL;  //initialize the lanes
	expressLane.pTail = NULL;
	normalLane.pHead = NULL;
	normalLane.pTail = NULL;

	printf("\t\t\t\t\tWELCOME TO GROCERY LANE SIMULATOR!!\n"); // main menu
	_sleep(2000);
	printf("How many minutes would you like to run the simulation? ");
	scanf("%d", &mins);
	printf("...set to run for %d minutes\n", mins);

	while (totalTime <= mins)
	{
		
		if (newExpCustomer == 0)
		{
			//arrival time for new express lane customer
			expArrival = rand() % 5 + 1;
			expHasArrived = expArrival;
			newExpCustomer = 1;
		}
		
		if (newNormCustomer == 0)
		{
			//arrival time for new normal lane customer
			normArrival = rand() % 5 + 1;
			normArrival += 3;
			normHasArrived = normArrival;
			newNormCustomer = 1;
		}
		
		if (totalTime != 0)
		{
			//If time has passed
			//initialize express lane customer service time & total time & (arrival time - 1)
			exp.serviceTime = expCustomer();
			exp.totalTime = 0;
			expArrival -= 1;

			//initialize normal lane customer service time & total time & (arrival time - 1)
			norm.serviceTime = normCustomer();
			norm.totalTime = 0;
			normArrival -= 1;

			if (totalTime % 10 == 0)
			{
				//Print out the current status of the express and normal lanes every 10 loops
				printf("Total Time: %d\n", totalTime);
				printf("Express Lane: ");
				printQueue(expressLane);
				isEmpty(&expressLane);
				printf("\n");
				printf("Normal Lane: ");
				printQueue(normalLane);
				isEmpty(&normalLane);
				printf("\n\n");
			}

			if (expArrival == 0)
			{
				//a new customer is going to enter the express lane
				//initialize a Data type variable and enqueue
				expCount++;
				exp.customerNumber = expCount;
				printf("EXPRESS LANE: (New Customer)\n");
				printf("Customer number %d.\n", exp.customerNumber);
				printf("Arrival time was %d minutes.\n", expHasArrived);
				printf("Total Time: %d\n", totalTime);
				enqueue(&expressLane, exp);
				printf("New Customer:[");
				printf("%d, %d, %d]", exp.customerNumber, exp.serviceTime, exp.totalTime);
				printf("\n\n");
				newExpCustomer = 0;
			}
			if (normArrival == 0)
			{
				//a new customer is going to enter the normal lane
				//initialize a Data type variable and enqueue
				normCount++;
				norm.customerNumber = normCount;
				printf("NORMAL LANE: (New Customer)\n");
				printf("Customer number %d.\n", norm.customerNumber);
				printf("Arrival time was %d minutes.\n", normHasArrived);
				printf("Total Time: %d\n", totalTime);
				enqueue(&normalLane, norm);
				printf("New Customer:[");
				printf("%d, %d, %d]\n", norm.customerNumber, norm.serviceTime, norm.totalTime);
				printf("\n");
				newNormCustomer = 0;
			}
			
		}
		// time is incrimented 
		//update the customers service and total times in line
		//dequeue if necessary 
		totalTime += 1;
		timePasses(&expressLane);
		dequeue(&expressLane, 1,totalTime);
		timePasses(&normalLane);
		dequeue(&normalLane, 2,totalTime);
	}
		
	return 0;
}
