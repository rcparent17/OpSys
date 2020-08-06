// my-wc.c
// written by Reilly Parent

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	
	FILE* fp; // file pointer for what gets passed to the command

	// read buffer setup
	int maxLength = 1024;
	char buffer[maxLength];

	// word and line count variables
	int wc = 0;
	int lc = 0;

	// open the file and exit if the file can't be found
	fp = fopen(argv[1], "r");
	if(fp == NULL){
		printf("my-wc: can not open file: %s\n", argv[1]);
		exit(1);
	}

	// loop through the lines in the file argv[1]
	while(fgets(buffer, maxLength, fp)){
		// loop through the buffer
		for(int bufferI = 0; bufferI < maxLength; bufferI++){
			//stop looping if we're at the end
			if(buffer[bufferI] == '\0'){
				break;
			}
			// if the character is a space or newline, we have arrived at the end of a word
			if(buffer[bufferI] == ' ' || (buffer[bufferI] == '\n')){
				wc++; // increment word count
			}
		}
		lc++; // increment every line
	}

	printf("%i lines, %i words\n", lc, wc); // print the output
	return 0;
}

