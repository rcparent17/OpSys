// my-uniq.c
// written by Reilly Parent

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// a method to get the number of concurrent items of arr[currentIndex] after arr[currentIndex]
int getNumDuplicates(char* arr[], int arrSize, int currentIndex){
	if(currentIndex == arrSize - 1) return 0; // if we're at the last element, return 0
	
	int numDuplicates = 0;

	// loop through the array
	for(int i = currentIndex + 1; i < arrSize; i++){
		// if arr[i] == arr[currentIndex], increment numDuplicates
		if(strcmp(arr[currentIndex], arr[i]) == 0){
			numDuplicates++;
		} else { // break if they aren't the same
			break;
		}
	}
	return numDuplicates;
}

int main(int argc, char* argv[]){
	
	// file pointer and length for the file passed to the command
	int fileLength = 0;
	FILE* fp;

	// read buffer setup
	int maxLength = 512;
	char buffer[maxLength];

	int maxLines = 1024;

	// allocate storage for reading lines in
	char* lines[maxLines];
	for(int line = 0; line < maxLines; line++){
		lines[line] = (char*) malloc(maxLength * sizeof(char));
	}

	// open argv[1] for reading
	fp = fopen(argv[1], "r");
	if(fp == NULL){
		printf("my-uniq: can not open file: %s\n", argv[1]);
		exit(1);
	}

	// read into the buffer and copy the strings into lines[], and increment fileLength every line
	while(fgets(buffer, maxLength, fp)){
		strcpy(lines[fileLength++], buffer);
	}

	// loop through lines
	for(int i = 0; i < fileLength; i++){
		printf("%s", lines[i]); // print the line
		i += getNumDuplicates(lines, fileLength, i); // increment i to avoid any concurrent instances of the line
	}

	return 0;
}
