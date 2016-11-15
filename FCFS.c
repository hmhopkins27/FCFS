/*
 * FCFS.c
 *
 *  Created on: Oct 27, 2016
 *      Author: hannahhopkins
 */

#include <stdio.h>
#include <stdlib.h>
#include "FCFS.h"

int main ()
{
	char fileName[20]; //string to hold the name of the file entered by the user
	process data[100], currentProcess; //array of structs to hold the process information
	int clockPulse = 0, counter = 0, processTime = 0, waitingTime = 0;
	bool cpu = false;

	//asking the user for the file name
	printf("Please enter the name of the file: ");
	scanf("%s", fileName);

	//calls function to read in the file and put process info into data array
	readFile(fileName, data);

	do
	{
		if(cpu == true) //if there is a process in the cpu
		{
			if(processTime == 0) //check and see if its run time is finished
			{
				cpu = false; //remove from cpu
				waitingTime = clockPulse - currentProcess.arrivalTime - currentProcess.timeToComplete;
				writeFile(clockPulse, waitingTime, currentProcess);
			}
		}

		//is the arrival time for any process equal to the current clock
		//pulse? If so, add process to the waiting queue.
		if(clockPulse == data[counter].arrivalTime)
		{
			do
			{
				enqueue(data[counter]);
				counter = counter + 1;
			} while(clockPulse == data[counter].arrivalTime);
		}

		if(cpu == true)
		{
			processTime--;
		}

		//if there is nothing in the CPU, dequeue from waiting queue
		//and put process into currentProcess and set the CPU to full
		else if((cpu == false) && (waitingQueueEmpty() == false))
		{
			currentProcess = dequeue();
			processTime = currentProcess.timeToComplete;
			cpu = true;
			processTime--;
		}

		clockPulse++;

	} while (counter != 100 || cpu != false || waitingQueueEmpty() == false);

	return(0);
}


void readFile(char fileName[20], process data[100])
{
	FILE *f1;

	f1 = fopen(fileName, "r");
	for(int i = 0; i < 100; i++)
	{
		fscanf(f1, "%s %d %d %d", data[i].processName, &data[i].arrivalTime,
				&data[i].timeToComplete, &data[i].priorityLevel);
	}
}


void writeFile(int clockPulse, int waitingTime, process currentProcess)
{
	FILE *output;

	output = fopen("output.txt", "a");
	fprintf(output, "%s %d %d %d\n", currentProcess.processName,
			currentProcess.arrivalTime, waitingTime, clockPulse);
	fclose(output);
}

void enqueue(process p)
{
	struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
	temp->processInfo = p;
	temp->link = NULL;

	//if the queue is empty
	if(waitingQueueEmpty() == true)
	{
		back = temp;
		front = temp;
		return;
	}

	back->link = temp;
	back = temp;
}

process dequeue()
{
	struct Node* temp = NULL;
	process processRemoved;

	temp = front;

	processRemoved = temp->processInfo;

	//the queue is empty and nothing can be removed
	if(waitingQueueEmpty() == true)
	{
		printf("An error has occurred.\n");
	}
	else
	{
		if(front == back)
		{
			front = back = NULL;
		}
		else
		{
			front = front->link;
		}
	}

	free(temp);

	return processRemoved;
}

bool waitingQueueEmpty()
{
	if(back == NULL && front == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}
