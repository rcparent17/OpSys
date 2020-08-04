// myshell.c
// written by Reilly Parent

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

// the main function. starts the shell and handles commands
int main(void){

	// input buffer setup
	int maxBuffLen = 200;
	char inBuffer[maxBuffLen];

	// pointer to hold tokens generated from strtok()
	char* currToken;
	
	// variable to keep track of the number of arguments in a command
	int numArgs = 0;
	
	// no one is going to have 15 arguments right?
	char* argBuffer[15];
	argBuffer[0] = ""; // initialize in case the first command is empty
	
	//pid variable for fork()
	int pid;
	
	// char index for replacing EOF and \n in commands
	int charIdx;

	// file descriptor for use with output redirection
	int outFd = 0;

	// store the default stdout (output to terminal) file descriptor
	int defaultStdout = dup(1);

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
			currToken = strtok(NULL, " "); // get the next token
		}

		// if the first argument is "quit", then quit!
		if(strcmp(argBuffer[0], "quit") == 0){
			printf("Goodbye!\n");	
			exit(0); // exit with status 0
		}
		// if the command is "sort"
		else if(strcmp(argBuffer[0], "sort") == 0){

			// if the command was longer than just sorting a file
			if(numArgs > 2){
				// if the 3rd argument is output redirection
				if(strcmp(argBuffer[2], ">") == 0){
					// if there is an output file specified
					if(numArgs != 3){
						// if the file doesn't exist
						if(access(argBuffer[3], F_OK) == -1){
							// open that file with create and write permissions, and give r/w permissions to everyone
							outFd = open(argBuffer[3], O_CREAT | O_WRONLY, 00666);
							// redirect stdout to that file
							dup2(outFd, 1);
						}
						else{ // don't overwrite the file if it exists
							printf("'%s' already exists and cannot be overwritten.\n", argBuffer[3]);
						}
					}
					else{ // tell the user if they dont name an output file
						printf("No output file named after '>'.\n");
					}
				}
				else{ // tell the user how to format commands
					printf("Improperly formatted command. Some correct commands are:\n\tsort a.txt\n\tsort a.txt > b.txt\n");
				}
			}
			else{ //otherwise, just sort the file
				// start a process to execute ./mysort on argBuffer[1]
				pid = fork();
				if(pid == 0){
					execlp("./mysort", "mysort", argBuffer[1], NULL);
				}
				else{
					waitpid(pid, NULL, 0); // wait for the child process to end
				}
			}
		}
		// if we don't know the command, tell the user!
		else {
			if(!strcmp(argBuffer[0], "") == 0){
				printf("Command not known: %s\n", argBuffer[0]);
			}
		}
		if(outFd != 0){ 
			close(outFd); // close the output file in case it's open
			outFd = 0; // reset outFd
		}
		dup2(defaultStdout, 1); // redirect output back to terminal
		numArgs = 0; // reset the argument counter at the end of the loop
	}
	return 0;
}
