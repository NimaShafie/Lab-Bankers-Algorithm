/*
Lab 3 - Banker's Algorithm
Comp 322/L
Nima Shafie
4/8/2022
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

/* Declare dynamic arrays and global variables*/
int MAX_PROCS = -1;
int MAX_RESOURCES = 1;

struct vectorType {
	int resource;
	int available;
} *vector = NULL, * resourceVector = NULL, * availableVector = NULL;
typedef struct vectorType type_vector;

struct arrayType {
	int value;
} *array = NULL, ** max_claim = NULL, ** allocation = NULL, ** need = NULL;
typedef struct arrayType type_array;

/*
there will be two vectors:

resource[j]     where j is the size of m
Resource vector: an m-element vector, where m is the number of resources and each entry
resource[j] records the total number of units of resource j.

available[j]     where j is the size of m
Available vector: an m-element vector, where m is the number of resources and each entry
available[j] records the number of units of resource j that are available.

all arrays will be 2d arrays, array[i][j]
or: array[number of processes][number of resources]
there will be three arrays:
max_claim[i][j]     where i is the size of n, and j is the size of m
max_claim[number of processes][number of resources]
Max claims array: an n x m-element array, where m is the number of resources and n is the number of
processes each entry maxclaim[i][j] contains an integer that records the maximum number of units of
resource j that process i may ever request.

allocation[i][j]     where i is the size of n, and j is the size of m
allocation[number of processes][number of resources]
Allocation array: an n x m-element array, where m is the number of resources and n is the number of
processes each entry allocation[i][j] contains an integer that records the number of units of
resource j that process i has actually been allocated.

need[i][j]     where i is the size of n, and j is the size of m
need[number of processes][number of resources]
Need array: an n x m array, where m is the number of resources and n is the number of processes
each entry need[i][j] contains an integer that records the number of units of resource j that
process i may need in the future.
*/


/***********************************************************/
// this will be called at the end of option 1 (first)
void PrintResource() {
	/* declare local variables */

	printf("\n\tUnits\tAvailable\n");
	printf("-----------------------------\n");
	/* for loop: print each resource index & number of total units and available units for each resource index */
	for (int i = 0; i <= MAX_RESOURCES; i++) {
		printf("r%d", i);
		printf("\t%d\t%d", resourceVector[i].resource, availableVector[i].available);
		printf("\n");
	}
	return;
}

/***************************************************************/
// this will be called at the end of option 1 (second)
void PrintMatrix() {
	/* declare local variables */
	// provides how many tab spaces we need between headers (Max Claim, Current, etc)
	int header_tab_space = MAX_RESOURCES++;


	// need to include a number of \t's = resource count to format correctly ater Max Claim
	//printf("\n\tMax Claim\t\t\tCurrent\t\t\t\tPotential\n");
	printf("\n\tMax Claim");
	for (int i = 0; i <= header_tab_space; i++) {
		printf("\t");
	}
	printf("Current");
	for (int i = 0; i <= header_tab_space; i++) {
		printf("\t");
	}
	printf("\tPotential\n");

	// this prints out the resource indices, we always iterate over 3 times for..
	// max_claim        current     potential
	for (int i = 0; i < 3; i++) {
		for (int resource_count = 0; resource_count < MAX_RESOURCES; resource_count++) {
			printf("\tr%d", resource_count);
		}
		printf("\t");
	}
	printf("\n--------");
	for (int i = 0; i <= header_tab_space; i++) {
		printf("------------------------------");
	}
	printf("\n");
	/* for loop: print each process index & number of total units and available units for each resource index */
	for (int i = 0; i < MAX_PROCS; i++) {
		printf("p%d", i);
		for (int j = 0; j < MAX_RESOURCES; j++) {
			printf("\t%d ", max_claim[i][j].value);
		}
		printf("\t");
		for (int k = 0; k < MAX_RESOURCES; k++) {
			printf("\t%d ", allocation[i][k].value);
		}
		printf("\t");
		for (int m = 0; m < MAX_RESOURCES; m++) {
			printf("\t%d ", need[i][m].value);
		}
		printf("\n");
	}
	printf("\n\n");
	return;
}


// option #1
/****************************************************************/
void EnterParameters() {
	/* declare local variables */
	// temp resource value to assign
	int r_temp = 0;
	int proc_count = 0;
	int resource_count = 0;

	/* prompt for number of processes and number of resources */
	printf("Enter total number of processes: ");
	scanf("%d", &MAX_PROCS);
	// ensure resources > 0
	do {
		if (MAX_RESOURCES <= 0) printf("\nResources must be greater than 0\n");
		printf("Enter total number of resources: ");
		scanf("%d", &MAX_RESOURCES);
	} while (MAX_RESOURCES <= 0);
	MAX_RESOURCES--;

	// used to determine the size of the available array
	int* proc_summation_of_resources = (int*)malloc(MAX_RESOURCES * sizeof(int));
	if (proc_summation_of_resources == NULL) {
		printf("\nNo memory is allocated for array.\n\n");
		exit(0);
	}
	for (int i = 0; i <= MAX_RESOURCES; i++)
		proc_summation_of_resources[i] = 0;

	/* allocate memory for vectors and arrays: resource, available, max_claim, allocated, need */
	vector = (type_vector*)malloc(MAX_RESOURCES * sizeof(vector));
	array = (type_array*)malloc((MAX_PROCS * MAX_RESOURCES) * sizeof(array));
	resourceVector = (type_vector*)malloc(MAX_RESOURCES * sizeof(vector));
	availableVector = (type_vector*)malloc(MAX_RESOURCES * sizeof(vector));
	max_claim = (type_array**)malloc((MAX_PROCS * MAX_RESOURCES) * sizeof(array));
	allocation = (type_array**)malloc((MAX_PROCS * MAX_RESOURCES) * sizeof(array));
	need = (type_array**)malloc((MAX_PROCS * MAX_RESOURCES) * sizeof(array));

	// Memory is allocated for 'n' elements 
	resourceVector = (type_vector*)malloc((MAX_RESOURCES) * sizeof(vector));
	availableVector = (type_vector*)malloc((MAX_RESOURCES) * sizeof(vector));
	if (vector == NULL || resourceVector == NULL || availableVector == NULL) {
		printf("\nNo memory is allocated for vector.\n\n");
		exit(0);
	}

	max_claim = (type_array**)malloc((MAX_PROCS * MAX_RESOURCES) * sizeof(array));
	allocation = (type_array**)malloc((MAX_PROCS * MAX_RESOURCES) * sizeof(array));
	need = (type_array**)malloc((MAX_PROCS * MAX_RESOURCES) * sizeof(array));
	for (int i = 0; i < MAX_PROCS; i++) {
		max_claim[i] = (type_array*)malloc(MAX_RESOURCES * sizeof(array));
		allocation[i] = (type_array*)malloc(MAX_RESOURCES * sizeof(array));
		need[i] = (type_array*)malloc(MAX_RESOURCES * sizeof(array));
	}
	if (max_claim == NULL || allocation == NULL || need == NULL) {
		printf("\nNo memory is allocated for array.\n\n");
		exit(0);
	}

	/* for each resource, prompt for number of units, set resource and available vectors indices*/
	printf("Enter number of units for resources (r0 to r%d): ", MAX_RESOURCES);
	for (int i = 0; i <= MAX_RESOURCES; i++) {
		scanf("%d", &r_temp);
		resourceVector[i].resource = r_temp;
	}

	/* for each process, for each resource, prompt for maximum number of units requested by process
	update max_claim and need arrays */
	for (proc_count = 0; proc_count < MAX_PROCS; proc_count++) {
		printf("Enter maximum number of units process p%d will request from each resource (r0 to r%d): ",
			proc_count, MAX_RESOURCES);
		// outter for loop [i] will iterate through all processes
		for (resource_count = 0; resource_count <= MAX_RESOURCES; resource_count++) {
			// inner for loop [j[ will iterate through all resources for each process
			scanf("%d", &r_temp);
			max_claim[proc_count][resource_count].value = r_temp;
		}
	}

	/* for each process, for each resource, prompt for number of resource units allocated to process */
	// same for loop setups as above, except we use allocation[i][j]
	// printf("Enter number of units of each resource (r0 to r%d) allocated to process p%d", resource_count,process_count);
	for (proc_count = 0; proc_count < MAX_PROCS; proc_count++) {
		printf("Enter number of units of each resource (r0 to r%d) allocated to process p%d: ",
			MAX_RESOURCES, proc_count);
		// outter for loop [proc_count] will iterate through all processes
		for (resource_count = 0; resource_count <= MAX_RESOURCES; resource_count++) {
			// inner for loop [resource_count] will iterate through all resources for each process
			scanf("%d", &r_temp);
			allocation[proc_count][resource_count].value = r_temp;
		}
	}

	// setting up the available vector from number of units of each resource allocated to each process
	for (resource_count = 0; resource_count <= MAX_RESOURCES; resource_count++) {
		for (int proc_count = 0; proc_count < MAX_PROCS; proc_count++) {
			// proc_summation_of_resources[proc_count] will hold the summation of all processes of a resource
			proc_summation_of_resources[resource_count] += allocation[proc_count][resource_count].value;
		}
		// ensures a non-negative available number
		if ((resourceVector[resource_count].resource - proc_summation_of_resources[resource_count]) >= 0) {
			availableVector[resource_count].available =
				resourceVector[resource_count].resource - proc_summation_of_resources[resource_count];
		}
		else {
			availableVector[resource_count].available = 0;
		}
	}

	// need array initalization
	for (proc_count = 0; proc_count < MAX_PROCS; proc_count++) {
		for (resource_count = 0; resource_count <= MAX_RESOURCES; resource_count++) {
			need[proc_count][resource_count].value =
				max_claim[proc_count][resource_count].value - allocation[proc_count][resource_count].value;
		}
	}

	/* print resource vector, available vector, max_claim array, allocated array, need array */
	PrintResource();
	PrintMatrix();
	return;
}


// option #2
// Run the Banker's algorithm to determine a safe sequence
/********************************************************************/
void BankerAlgo() {
	// determine if option #1 has been run or not (prompt user to enter option 1 if not run yet)
	if (MAX_PROCS == -1) {
		printf("\nParameters must first be entered before determining safe sequence.\n"
			"Please enter option #1 first.\n\n");
		return;
	}

	/* declare local variables, including vector to indicate if process is safely sequenced and "num_sequenced" count*/
	int num_sequenced_count = 0;
	int proc_count = 0;
	int resource_count = 0;
	int max_tests = MAX_PROCS;
	bool unsafe_process = false;
	bool* safeVec = (bool*)malloc(MAX_PROCS * sizeof(bool));
	int* seqVec = (int*)malloc(MAX_PROCS * sizeof(int));
	if (safeVec == NULL || seqVec == NULL) {
		printf("\nNo memory is allocated for vector.\n\n");
		exit(0);
	}
	for (int i = 0; i < MAX_PROCS; i++) {
		safeVec[i] = false;
		seqVec[i] = -1;
	}


	// when maxTests == MAX_PROCS + 1
	// then we found no changes, and we're in a deadlock, end and output to user

	/* while not all processed are sequenced */
	while (num_sequenced_count < MAX_PROCS) {
		for (proc_count = 0; proc_count < MAX_PROCS; proc_count++) {
			if (!safeVec[proc_count]) {
				printf("Checking:");
				/* if process has not been safely sequenced yet */
				printf(" <");
					// for each resource
				for (resource_count = 0; resource_count < MAX_RESOURCES; resource_count++) {
					/* check for safe sequencing by comparing process' need vector to available vector */
					printf(" %d", need[proc_count][resource_count].value);
					// entering this if statement means too many resources are being requested
					if (need[proc_count][resource_count].value > availableVector[resource_count].available) {
						unsafe_process = true;
					}
				}
				printf(" > <= <");
				for (resource_count = 0; resource_count < MAX_RESOURCES; resource_count++) {
					printf(" %d", availableVector[resource_count].available);
				}
				printf(" > :");
				if (unsafe_process) {
					printf("p%d could not be sequenced\n", proc_count);
					max_tests--;
				}
				else {
					printf("p%d safely sequenced\n", proc_count);
					safeVec[proc_count] = true;
					seqVec[num_sequenced_count] = proc_count;
					max_tests = (MAX_PROCS - 1);

					for (resource_count = 0; resource_count < MAX_RESOURCES; resource_count++) {
						availableVector[resource_count].available += allocation[proc_count][resource_count].value;
					}
					num_sequenced_count++;
				}
			}
			unsafe_process = false;
			if (max_tests == 0) {
				printf("\nSystem has an unsafe state. Deadlock reached.\n");
				return;
			}
		}
	}
	// we only arrive here if a safe state has been reached, inform user now
	printf("\nSafe Sequence = ");
	for (proc_count = 0; proc_count < MAX_PROCS; proc_count++) {
		if ((proc_count + 1) == MAX_PROCS) printf("P%d\n\n", seqVec[proc_count]);
		else printf("P%d, ", seqVec[proc_count]);
	}
	return;
}


// option #3
// Quit program and free memory
/********************************************************************/
void FreeMemoryQuitProgram() {
	/* check if vectors/array are not NULL--if so, free each vector/array */
	if (vector != NULL) {
		free(vector);
		vector = NULL;
	}
	if (array != NULL) {
		free(array);
		array = NULL;
	}
	if (resourceVector != NULL) {
		free(resourceVector);
		resourceVector = NULL;
	}
	if (availableVector != NULL) {
		free(availableVector);
		availableVector = NULL;
	}
	if (max_claim != NULL) {
		free(max_claim);
		max_claim = NULL;
	}
	if (allocation != NULL) {
		free(allocation);
		allocation = NULL;
	}
	if (need != NULL) {
		free(need);
		need = NULL;
	}
	printf("\nMemory has been freed\n");
	return;
}


/***************************************************************/
int main() {
	int i = 0;
	enum { PARAM, BANKERS, QUIT, INVALID } menuChoice;

	while (i != 3) {
		printf("Batch Scheduling\n------------------------------\n");
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