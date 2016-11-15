/*
 * FCFS.h
 *
 *  Created on: Oct 27, 2016
 *      Author: hannahhopkins
 */

#ifndef FCFS_H_
#define FCFS_H_

typedef enum Boolean
{
	false,
	true
} bool;

typedef struct
{
   char processName[2];
   int arrivalTime;
   int timeToComplete;
   int priorityLevel;
} process;

struct Node
{
	process processInfo;
	struct Node* link;
};

struct Node* front = NULL;
struct Node* back = NULL;

void readFile(char fileName[20], process data[100]);
void writeFile(int clockPulse, int waitingTime, process currentProcess);
void enqueue(process p);
process dequeue();
bool waitingQueueEmpty();

#endif /* FCFS_H_ */
