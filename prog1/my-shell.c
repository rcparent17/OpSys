// my-shell.c
// written by Reilly Parent

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO1 "/tmp/pipe1fifo"
#define FIFO2 "/tmp/pipe2fifo"

// a method that runs commands entered into my-shell. handles piped and non-piped commands
void executeCommand(char* args[], int numArgs, int numPipes){
	
	// pid variables for fork()
	int pid1;
	int pid2;
	int pid3;

	// chars to store execute strings (commands)
	char cmd1[20];
	char cmd2[20];
	char cmd3[20];
	
	// 2 file descriptors for writing to each FIFO
	int fdwr1 = -1;
	int fdwr2 = -1;
	int ogFd = dup(1); // save original stdout (terminal) file descriptor

	// little trick to prepend "./" to the command for use in execlp()
    	char* ds = "./";
    	char* dup;
	strcpy(cmd1, args[0]);
    	sprintf(cmd1, "%s%s", ds, (dup=strdup(cmd1)));
	free(dup);

	//do it for the 2nd command if it exists
	if(numArgs == 4){
		char* dup;
		strcpy(cmd2, args[3]);
    		sprintf(cmd2, "%s%s", ds, (dup=strdup(cmd2)));
		free(dup);
	}

	// same for 3rd
	if(numArgs == 6){
		char* dup;
		strcpy(cmd3, args[5]);
    		sprintf(cmd3, "%s%s", ds, (dup=strdup(cmd3)));
		free(dup);
	}


	// if there are no pipes, start a child process to run the command
	if(numPipes == 0){
		pid1 = fork();
		if(pid1 == 0){
			execlp(cmd1, args[0], args[1], NULL);
		}
		else{
			waitpid(pid1, NULL, 0);
		}
	}
	else if(numPipes == 1){ // if there is 1 pipe
		mkfifo(FIFO1, 0666); // make fifo1

		pid1 = fork(); // start a child process to run the command
		if(pid1 == 0){
			// redirect stdout to fifo1
			fdwr1 = open(FIFO1, O_WRONLY);
			dup2(fdwr1, 1);
			close(fdwr1);

			execlp(cmd1, args[0], args[1], NULL); //write to fifo1
		}
		else{
			pid2 = fork(); // start another process to run the 2nd command
			if(pid2 == 0){
				dup2(ogFd, 1); // reset stdout
				execlp(cmd2, args[3], FIFO1, NULL); // read from fifo1	
			}
			else{
				waitpid(pid2, NULL, 0);
			}
		}
	}
	else if(numPipes == 2){ // do everything you would if there were only 1 pipe
		mkfifo(FIFO1, 0666);
		mkfifo(FIFO2, 0666); // but make a 2nd fifo

		pid1 = fork();
		if(pid1 == 0){
			fdwr1 = open(FIFO1, O_WRONLY);
			dup2(fdwr1, 1);
			close(fdwr1);
			execlp(cmd1, args[0], args[1], NULL); //write to fifo1
		}
		else{
			pid2 = fork();
			if(pid2 == 0){
				// and redirect output of the 2nd command to FIFO2
				fdwr2 = open(FIFO2, O_WRONLY);
				dup2(fdwr2, 1);
				close(fdwr2);
				execlp(cmd2, args[3], FIFO1, NULL); // read from fifo 1 and write to fifo 2
			}
			else{
				// start a 3rd process to run the 3rd and final command 
				pid3 = fork();
				if(pid3 == 0){
					dup2(ogFd, 1); // reset stdout
					execlp(cmd3, args[5], FIFO2, NULL); // read fifo 2
				}
				else{
					waitpid(pid3, NULL, 0);
				}
			}
			wait(NULL);
		}
		// remove the fifo files
		unlink(FIFO1);
		unlink(FIFO2);
	}
}


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
	int maxArgs = 15;
	char* argBuffer[maxArgs];
	argBuffer[0] = ""; // initialize in case the first command is empty

	// char index for replacing EOF and \n in commands
	int charIdx;

	// number of pipes if a command is piped
	int numPipes = 0;

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
			if(strcmp(currToken, "|") == 0) numPipes++; // if the token is a pipe, increment numPipes
			argBuffer[numArgs++] = currToken; // store it in the argBuffer and increment the arg counter
			currToken = strtok(NULL, " "); // get the next token (not really sure why NULL is passed instead of inBuffer though)
		}

		if(numPipes > 2){ // don't run commands with more than 2 pipes
			printf("Only 2 pipes are allowed per command.\n");
		}
		else if(strcmp(argBuffer[0], "") != 0 && numArgs != 1 && numArgs != 2 && numArgs != 4 && numArgs != 6){ // if the command has an invalid number of arguments
			printf("This command does not have a proper amount of arguments. Perhaps a pipe doesn't have a destination, or the syntax of a command is incorrect.\n");
		}
		else{
			// if the first argument is "quit", then quit!
			if(strcmp(argBuffer[0], "quit") == 0){
				printf("Goodbye!\n");
				exit(0); // exit with status 0
			}
			else if(strcmp(argBuffer[0], "my-cat") == 0 || strcmp(argBuffer[0], "my-wc") == 0 ||strcmp(argBuffer[0], "my-uniq") == 0){
				executeCommand(argBuffer, numArgs, numPipes);
			}
			else{ // if we don't know the command, tell the user!
				if(!strcmp(argBuffer[0], "") == 0){
					printf("Command not known: %s\n", argBuffer[0]);
				}
			}
		}

		numArgs = 0; // reset the argument counter at the end of the loop
		numPipes = 0; // reset pipe counter
	}
	
	return 0;
}
