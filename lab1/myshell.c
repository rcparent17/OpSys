#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(void){

	char inBuffer[200];
	char* currToken;
	int numArgs = 0;
	char* argBuffer[15];

	while(inBuffer != "quit\r\n"){

		printf("myShell> ");
		fgets(inBuffer, 200, stdin);
		printf("%s\n", inBuffer);
		currToken = strtok(inBuffer, " ");
		while(currToken){ 
			argBuffer[numArgs] = currToken;
			numArgs++;
			currToken = strtok(NULL, " ");
		}

		char* args[numArgs++];
		for(int i = 0; i < numArgs; i++){
			if(i == numArgs - 1){
				args[i] = NULL;
			}
			else{
				args[i] = argBuffer[i];
			}
			//printf("%s\n", args[i]);
		}
		int pid = fork();
		if(pid == 0){
			execvp(args[0], args);
		}
		else{
			wait(NULL);
		}
		numArgs = 0;
	}
	return 0;

}
