#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	
	FILE* fp;
	int maxLength = 1024;
	char buffer[maxLength];

	int wc = 0;
	int lc = 0;

	fp = fopen(argv[1], "r");
	if(fp == NULL){
		printf("myWC: can not open file: %s\n", argv[1]);
		return 1;
	}

	while(fgets(buffer, maxLength, fp)){
		for(int bufferI = 0; bufferI < maxLength; bufferI++){
			if(buffer[bufferI] == '\0'){
				break;
			}
			if(buffer[bufferI] == ' ' || (buffer[bufferI] == '\n')){
				wc++;
			}
		}
		lc++;
	}

	printf("%i %i\n", lc, wc);
	return 0;
}

