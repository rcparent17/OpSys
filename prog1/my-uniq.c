#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*int strArrayContains(char* arr[], int arrSize, char* str){
	for(int j = 0; j < arrSize; j++){
		if(strcmp(arr[j], str) == 0){
			return 1;
		}
	}
	return 0;
}*/

int getNumDuplicates(char* arr[], int arrSize, int currentIndex){
	if(currentIndex == arrSize - 1) return 0;
	
	int numDuplicates = 0;

	for(int i = currentIndex + 1; i < arrSize; i++){
		if(strcmp(arr[currentIndex], arr[i]) == 0){
			numDuplicates++;
		} else {
			break;
		}
	}
	return numDuplicates;
}

int main(int argc, char* argv[]){
	
	int fileLength = 0;
	FILE* fp;
	int maxLength = 512;
	char buffer[maxLength];

	int maxLines = 1024;
	char* lines[maxLines];
	for(int line = 0; line < maxLines; line++){
		lines[line] = (char*) malloc(maxLength * sizeof(char));
	}

	fp = fopen(argv[1], "r");
	if(fp == NULL){
		printf("myUniq: can not open file: %s\n", argv[1]);
		return 1;
	}

	while(fgets(buffer, maxLength, fp)){
		strcpy(lines[fileLength++], buffer);
	}

	int i;
	for(i = 0; i < fileLength; i++){
		printf("%s", lines[i]);
		i += getNumDuplicates(lines, fileLength, i);
	}

	return 0;
}
