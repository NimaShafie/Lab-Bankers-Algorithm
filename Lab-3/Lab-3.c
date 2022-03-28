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

/*
typedef struct dynamic_array
{
	int* data;
	int capacity; // total capacity
	int size; // number of elements in vector
} vector;
*/

struct vectorType {
    int resource;
    int available;
} *vector = NULL;
typedef struct vectorType type_vector;

struct arrayType {
    int resource;
    int process;
} *array = NULL;
typedef struct arrayType type_array;

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

resource[j]     where j is the size of m
Resource vector: an m-element vector, where m is the number of resources and each entry resource[j] records the total number of units of resource j.

available[j]     where j is the size of m
Available vector: an m-element vector, where m is the number of resources and each entry available[j]
records the number of units of resource j that are available.

n x m meaning, n by m, which equals n * m total elements,   rows x columns
so if n = 3, m = 1,     3 x 1 ==
x
x
x
3 total elements

if (a=2) x (b=4)
a b b b
a b b b
8 total elements

n m m m
n m m m
2 x 4 array (or n = 2, m = 4)
in the following, to access the j'th element, we use maxClaim[i = 1][j = 1]
n m m m
n j m m

all arrays will be 2d arrays, array[i][j]
there will be three arrays:
max_claim[i][j]     where i is the size of n, and j is the size of m
Max claims array: an n x m-element array, where m is the number of resources and n is the number of processes
each entry maxclaim[i][j] contains an integer that records the maximum number of units of resource j that process i may ever request.

allocation[i][j]     where i is the size of n, and j is the size of m
Allocation array: an n x m-element array, where m is the number of resources and n is the number of processes
each entry allocation[i][j] contains an integer that records the number of units of resource j that process i has actually been allocated.

need[i][j]     where i is the size of n, and j is the size of m
Need array: an n x m array, where m is the number of resources and n is the number of processes
each entry need[i][j] contains an integer that records the number of units of resource j that process i may need in the future.
*/



/***********************************************************/
// this will be called at the end of option 1 (first)
void PrintResource() {
	/* declare local variables */

    printf("\nResource\t\tUnits\t\tAvailable\n");
    printf("------------------------------------------------\n");

	/* for loop: print each resource index */

	/* for loop: print number of total units and available units of each resource index */
	return;
}


/***************************************************************/
// this will be called at the end of option 1 (second)
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


    // vectors = resource + available
    // 2d arrays = max_claim, allocated, need
	/* allocate memory for vectors and arrays: resource, available, max_claim, allocated, need */
    vector = (type_vector*)malloc((MAX_PROCS * MAX_RESOURCES) * sizeof(vector));        // trying to see if we can just use two of these
    array = (type_vector*)malloc((MAX_PROCS * MAX_RESOURCES) * sizeof(array));

    // typedef struct vectorType type_vector;	// pcb = struct Node
    // vector --> *process = NULL;
    // tableType = typeVec
    /*
    process = (table_typedef*)malloc(MAX_PROCS * sizeof(process)); // Memory is allocated for 'n' elements 
	if (process == NULL) {
		printf("\nNo memory is allocated.\n\n");
		exit(0);
	}
    */


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