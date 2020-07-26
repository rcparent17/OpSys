// myshell.c
// written by Reilly Parent

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

// the main function. starts the shell and handles commands
int main(void){

	// input buffer setup
	int maxBuffLen = 200;
	char inBuffer[maxBuffLen];

	// pointer to hold tokens generated from strtok()
	char* currToken;
	
	// variable to keep track of the nnumber of arguments in a command
	int numArgs = 0;
	
	// no one is going to have 15 arguments right?
	char* argBuffer[15];
	argBuffer[0] = ""; // initialize in case the first command is empty
	
	//pid variable for fork()
	int pid;
	
	// char index for replacing EOF and \n in commands
	int charIdx;

	// forever, lol
	while(1){
		printf("myShell> ");

		// get user input and store it in inBuffer
		fgets(inBuffer, maxBuffLen, stdin);

		// replace EOF and \n with null character
		for(charIdx = 0; charIdx < maxBuffLen; charIdx++){
			if(inBuffer[charIdx] == '\n' || inBuffer[charIdx] == EOF){
				inBuffer[charIdx] = '\0';
				}
		}

		// strtok is kinda similar to split() in python. this gets the first token from the string split by a space
		currToken = strtok(inBuffer, " ");
		
		//while the token isn't empty
		while(currToken){ 
			argBuffer[numArgs++] = currToken; // store it in the argBuffer and increment the arg counter
			currToken = strtok(NULL, " "); // get the next token (not really sure why NULL is passed instead of inBuffer though)
		}

		// if the first argument is "quit", then quit!
		if(strcmp(argBuffer[0], "quit") == 0){
			printf("Goodbye!\n");
			exit(0); // exit with status 0
		}
		// if the command is "sort"
		else if(strcmp(argBuffer[0], "sort") == 0){

			// start a process to execute ./mysort on argBuffer[1]
			pid = fork();
			if(pid == 0){
				execlp("./mysort", "mysort", argBuffer[1], NULL);
			}
			else{
				waitpid(pid, NULL, 0); // wait for the child process to end
			}
		}
		// if we don't know the command, tell the user!
		else {
			if(!strcmp(argBuffer[0], "") == 0){
				printf("Command not known: %s\n", argBuffer[0]);
			}
		}
		numArgs = 0; // reset the argument counter at the end of the loop
	}
	
	return 0;
}
