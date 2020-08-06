// my-cat.c
// written by Reilly Parent

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

	// file pointer for reading
	FILE* fp;

	// read buffer
	int maxLength = 1024;
	char buffer[maxLength];

	// open argv[1] for reading
	fp = fopen(argv[1], "r");
	if(fp == NULL){
		printf("my-cat: can not open file: %s\n", argv[1]);
		exit(1);
	}

	// loop through all of the lines in the file argv[1] and print them
	while(fgets(buffer, maxLength, fp)){
		printf("%s", buffer);
	}

	return 0;
}
