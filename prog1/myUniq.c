#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
	
	int uniq = 0;
	int fileLength = 0;
	
	FILE* fp;
	int maxLength = 1024;
	char buffer[maxLength];
	char currLine[maxLength];

	int maxLines = 1000;
	char* lines[maxLines];

	fp = fopen(argv[1], "r");
	if(fp == NULL){
		printf("myUniq: can not open file: %s\n", argv[1]);
		return 1;
	}

	while(fgets(buffer, maxLength, fp)){
		for(int i = 0; i < maxLength; i++){
			if(buffer[i]=='\n' || buffer[i] = EOF){
				buffer[i] = '\0';
			}
		}
		lines[fileLength++] = buffer;
	}

	int i, j;
	for(i = 0; i < fileLength; i++){
		for(j = 0; j < fileLength; j++){
			if(i != j 

	return 0;
}
