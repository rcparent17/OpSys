#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	
	FILE* fp;
	int maxLength = 1024;
	char buffer[maxLength];

	fp = fopen(argv[1], "r");
	if(fp == NULL){
		printf("myCat: can not open file: %s\n", argv[1]);
		return 1;
	}

	while(fgets(buffer, maxLength, fp)){
		for(int i = 0; i < maxLength; i++){
			if(buffer[i]=='\0'){
				break;
			}
			printf("%c", buffer[i]);
		}
		printf("\n");
	}

	return 0;
}
