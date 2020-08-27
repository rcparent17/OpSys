#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdint.h>
#define MAX_NUMS 20
#define NUM_THREADS 4

// wrapper structure to pass multiple variables to the threads
typedef struct arrData {
	int* nums;
	int size;
} arrData;

// unused function to display an array
// void dispList(arrData ad){for(int i = 0; i < ad.size; i++) printf("%i\n", ad.nums[i]);}

// takes an arrData struct as a void pointer and returns the average of the array
void* average(void* p){
	arrData ad = *((arrData *) p); // cast to struct
	int average = 0;
	for(int i = 0; i < ad.size; i++){
		average += ad.nums[i];
	}
	average /= ad.size;
	pthread_exit((void*)(intptr_t)average);
}
// takes a sorted arrData struct as a void pointer and returns the largest number in the array
void* max(void* p){
	arrData ad = *((arrData *) p); // cast to struct
	int max = ad.nums[ad.size - 1];
	pthread_exit((void*)(intptr_t)max);
}
// takes a sorted arrData struct as a void pointer and returns the smallest number the array
void* min(void* p){
	arrData ad = *((arrData *) p);
	int min = ad.nums[0];
	pthread_exit((void*)(intptr_t)min);
}
// takes a sorted arrData struct as a void pointer and returns the middle element
void* median(void* p){
	arrData ad = *((arrData *) p);
	return (void*)(intptr_t)ad.nums[ad.size/2];
}

// simple implementation of bubblesort that sorts the array in the array in an arrData struct
void sort(arrData ad){
	for(int i = 0; i < ad.size - 1; i++){
		for(int j = 0; j < ad.size - i - 1; j++){
			if(ad.nums[j] > ad.nums[j+1]){
				int temp = ad.nums[j];
				ad.nums[j] = ad.nums[j+1];
				ad.nums[j+1] = temp;
			}
		}
	}
}

int main(int argc, char* argv[]){
	if(argc - 1 > MAX_NUMS || argc == 1){ // make sure there is a correct number of arguments
		printf("At least 1 integer argument must be provided, and a maximum of 20 may be provided.\n");
		return 1;
	}

	// set up an arrData struct
	arrData ad;
	ad.size = argc - 1; // the program name isn't a number!
	ad.nums = (int*) malloc((ad.size) * sizeof(int)); // allocate space for all the numbers
	for(int i = 1; i < argc; i++){ // convert the arguments to ints and store them
		ad.nums[i - 1] = atoi(argv[i]);
	}

	sort(ad); // sort the list so our functions work
	
	pthread_t tids[NUM_THREADS]; // array for thread ids

	// set up void pointer array to get the return values (ints) from the threads
	void* returns[NUM_THREADS];
	for(int i = 0; i < NUM_THREADS; i++)
		returns[i] = (void*) malloc(sizeof(int));

	// launch all four threads on ad
	pthread_create(&tids[0], NULL, average, &ad);
	pthread_create(&tids[1], NULL, min, &ad);
	pthread_create(&tids[2], NULL, max, &ad);
	pthread_create(&tids[3], NULL, median, &ad);

	// wait for the threads to finish and store their results
	for(int i = 0; i < NUM_THREADS; i++)
		pthread_join(tids[i], returns[i]);

	// display the results
	printf("Thread 1 -> The average value is %i\n", *(int*)returns[0]);
	printf("Thread 2 -> The minimum value is %i\n", *(int*)returns[1]);
	printf("Thread 3 -> The maximum value is %i\n", *(int*)returns[2]);
	printf("Thread 4 -> The median  value is %i\n", *(int*)returns[3]);

	return 0;
}

