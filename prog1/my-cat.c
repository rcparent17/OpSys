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
		printf("%s", buffer);
	}

	return 0;
}
