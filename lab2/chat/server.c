#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define CHAT_FIFO "/tmp/chatFifo"
#define MAX_LENGTH 512

int main(void){

	mkfifo(CHAT_FIFO, 0666); // make the fifo

	char inBuffer[MAX_LENGTH]; // input buffer
	char readBuffer[MAX_LENGTH]; // fifo read buffer
	
	int fdRead; // read file descriptor
	int fdWrite; // write file descriptor

	int quit = 0; // bool to keep track of if the user has quit

	while(1){
		fdRead = open(CHAT_FIFO, O_RDONLY); // open the fifo for reading, and read
		read(fdRead, readBuffer, MAX_LENGTH);
		if(strcmp(readBuffer, "quit\n") == 0){ // tell the user if the other person quits and exit
			printf("The other user has exited the session.\n");
			break;
		}

		//get message from user
		printf("			Other User: %s\n", readBuffer);
		printf("Type a message: ");
		fgets(inBuffer, MAX_LENGTH, stdin);

		// set quit to true if the user types quit
		if(strcmp(inBuffer, "quit\n") == 0){
			quit = 1;
		}

		//send the message even if we quit
		fdWrite = open(CHAT_FIFO, O_WRONLY);
		write(fdWrite, inBuffer, strlen(inBuffer)+1);
		close(fdRead);
		close(fdWrite);

		// exit if we quit
		if(quit){
			printf("Goodbye!\n");
			break;
		}
	}
	unlink(CHAT_FIFO); // close the FIFO
	return 0;
}
