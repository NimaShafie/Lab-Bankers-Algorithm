/*
Lab 3 - Banker's Algorithm
Comp 322/L
Nima Shafie
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

/* Declare dynamic arrays and global variables*/
int MAX_PROCS;
int MAX_RESOURCES = 1;

typedef struct dynamic_array
{
	int* data;
	int capacity; // total capacity
	int size; // number of elements in vector
} vector;

/*
struct TableType {
	int id;
	int arrival;
	int total_cpu;
	int total_remaining;
	bool done;
	int start_time;
	bool already_started;
	int end_time;
	int turnaround_time;
} *process = NULL;
typedef struct TableType table_typedef;	// pcb = struct Node
/* 

/*
there will be two vectors:
Resource vector: an m-element vector, where m is the number of resources and each entry resource[j] records the total number of units of resource j.
Available vector: an m-element vector, where m is the number of resources and each entryavailable[j] records the number of units of resource j that are available.

there will be three arrays:
Max claims array: an nxm-element array, where m is the number of resources and n is the number of processes and each entry maxclaim[i][j] contains an integer that records the maximum number of units of resource j that process i may ever request.
Allocation array: an nxm-element array, where m is the number of resources and n is the number of processes and each entry allocation[i][j] contains an integer that records the number of units of resource j that process i has actually been allocated.
Need array: an nxm array, where m is the number of resources and n is the number of processes and each entry need[i][j] contains an integer that records the number of units of resource j that process i may need in the future.
*/


/***********************************************************/
void PrintResource() {
	/* declare local variables */

	/* for loop: print each resource index */

	/* for loop: print number of total units and available units of each resource index */
	return;
}


/***************************************************************/
void PrintMatrix() {
	/* declare local variables */

	/* for loop: print each resource index */
	/* for each process: */
		/* for each resource: */
			/* print maximum number of units each process may request, is allocated, and needs from each resource */

	return;
}


// option #1
/****************************************************************/
void EnterParameters() {
	/* declare local variables */
	int r_min = 0;  // resource value
	int r_max = 0;

	/* prompt for number of processes and number of resources */
	printf("Enter total number of processes: ");
	scanf("%d", &MAX_PROCS);
	// ensure resources > 0
	do {
		if (MAX_RESOURCES <= 0) printf("\nResources must be greater than 0\n");
		printf("Enter total number of resources: ");
		scanf("%d", &MAX_RESOURCES);
	} while (MAX_RESOURCES <= 0);


	/* allocate memory for vectors and arrays: resource, available, max_claim, allocated, need */


	/* for each resource, prompt for number of units, set resource and available vectors indices*/
	printf("\nEnter number of units for resources (r%d to r%d): ", r_min, r_max);   // r_min = starting index for resource vector, r_max = ending index for resource vector (r_size)
	for (int i = 0; i < MAX_RESOURCES; i++) {
		//scanf("%d", &);
	}

	/* for each process, for each resource, prompt for maximum number of units requested by process, update max_claim and need arrays */
	/* for each process, for each resource, prompt for number of resource units allocated to process */
	/* print resource vector, available vector, max_claim array, allocated array, need array */
	return;
}


// option #2
// Run the Banker's algorithm to determine a safe sequence
/********************************************************************/
void BankerAlgo() {

	/* declare local variables, including vector to indicate if process is safely sequenced and "num_sequenced" count*/


	/* while not all processed are sequenced */
		/* for each process */
			/* if process has not been safely sequenced yet 8?
				/* for each resource */
				/* check for safe sequencing by comparing process' need vector to available vector */
				/* if each resource is available */
				/* print message that process had been safely sequenced */
				/* update number of available units of resource */
				/* for each resource */
					/* free all resources allocated to process */
					/* increment number of sequenced processes */
	return;
}


// option #3
// Quit program and free memory
/********************************************************************/
void FreeMemoryQuitProgram() {
	/* check if vectors/array are not NULL--if so, free each vector/array */
	//if (process != NULL) printf("\nDestroying remaining processes\n");
	//free(process);
	return;
}


/***************************************************************/
int main() {
	int i = 0;
	enum { PARAM, BANKERS, QUIT, INVALID } menuChoice;

	while (i != 3) {
		printf("Batch Scheduling\n--------------------------\n");
		printf("1) Enter parameters\n");
		printf("2) Determine safe sequence\n");
		printf("3) Quit program and free memory\n");
		printf("\nEnter selection: ");
		scanf("%d", &i);
		if (i == 1) menuChoice = PARAM;
		else if (i == 2) menuChoice = BANKERS;
		else if (i == 3) menuChoice = QUIT;
		else menuChoice = INVALID;

		switch (menuChoice) {
		case PARAM:
			EnterParameters();
			break;
		case BANKERS:
			BankerAlgo();
			break;
		case QUIT:
			FreeMemoryQuitProgram();
			break;
		case INVALID:
			printf("Invalid selection made, try again.\n\n");
		}
	};
	printf("\nThank you for using the Banker's Algorithm program, have a good day!\n");
	return 1; /* indicates success */
}