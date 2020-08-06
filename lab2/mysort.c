// mysort.c
// written by Reilly Parent

#include <stdio.h>
#include <stdlib.h>


// a function to swap the values of 2 int variables. used for sorting
// takes in 2 pointers to the variables that need swapped
void swap(int* a, int* b){
	int temp = *b;
	*b = *a;
	*a = temp;
}

// this function loops through the list once and returns 0 if it sees an element out of place
// takes in an array and the length of that array
int isSorted(int arr[], int length){
	for(int i = 0; i < length - 1; i++){
		if(arr[i] > arr[i + 1]){
			return 0; // array is not sorted
		}
	}
	return 1; // array is sorted
}

// a bubble sort function that returns a NEW sorted array (does not modify the original)
// efficient? nope. easy? yup.
// takes in an unsorted array and the length of that array.
int* bubbleSort(int unsorted[], int length){
	int* sorted = unsorted;

	// while the list isn't sorted
	while(!isSorted(sorted, length)){
		for(int i = 0; i < length - 1; i++){
			// if we see an element out of place, swap 'em!
			if(sorted[i] > sorted[i + 1]){
				swap(&sorted[i], &sorted[i+1]);
			}
		}
	}

	return sorted; // return the sorted array
}

// this function prints an array of integers
// takes in an array and the length of that array
void printNums(int nums[], int length){
	for(int i = 0; i < length; i++){
		printf("%i\n", nums[i]);
	}
}

// the main method. run this program like this:
//
// ./mysort numFile.txt

int main(int argc, char* argv[]){

	FILE* fp; // file pointer for number file

	// input buffer setup
	int maxLineLength = 100;
	char inBuffer[maxLineLength];

	// number buffer setup
	int maxNums = 1000;
	int arrBuffer[maxNums];
	int arrLength = 0; // final array length counter

	// open the file and return 1 if it can't be opened
	fp = fopen(argv[1], "r");
	if(fp == NULL){
		printf("mysort: can not open file: %s\n", argv[1]);
		return 1;
	}

	// while the file still has lines to be read
	while(fgets(inBuffer, maxNums, fp)){
		// convert inbuffer to an int, add it to the intbuffer, and increment the counter all in one line
		arrBuffer[arrLength++] = atoi(inBuffer);
	}

	// create the actual array that gets sorted
	int arr[arrLength];
	for(int i = 0; i < arrLength; i++){
		arr[i] = arrBuffer[i];
	}
	
	//print the sorted array
	printNums(bubbleSort(arr, arrLength), arrLength);

	return 0;
}
