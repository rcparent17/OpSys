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
	mkfifo(CHAT_FIFO, 0666); // make the FIFO wile with read/write permission for everyone

	char inBuffer[MAX_LENGTH]; // input buffer
	char readBuffer[MAX_LENGTH]; // FIFO read buffer
	
	int fdRead; // read file descriptor
	int fdWrite; // write file descriptor

	while(1){ // forever
		fdWrite = open(CHAT_FIFO, O_WRONLY); // open the fifo for writing
		printf("Type a message (or 'quit' to quit): ");
		fgets(inBuffer, MAX_LENGTH, stdin); // get user input
		if(strcmp(inBuffer, "quit\n") == 0){ // if the user quits
			printf("Goodbye!\n");
			write(fdWrite, inBuffer, strlen(inBuffer) + 1); // tell the other user
			break; // exit the loop
		}
		else{
			write(fdWrite, inBuffer, strlen(inBuffer) + 1); // write the message to fifo
			close(fdWrite);
			fdRead = open(CHAT_FIFO, O_RDONLY); // open the fifo for reading, and read
			read(fdRead, readBuffer, MAX_LENGTH); 
			if(strcmp(readBuffer, "quit\n") == 0){ // if we recieve a 'quit' tell the user and exit the loop
				printf("The other user has exited the session.\n");
				break;
			}
			else{ // print the message
				printf("			Other User: %s\n", readBuffer);
				close(fdRead);
			}
		
		}
	}
	unlink(CHAT_FIFO); // close the fifo
	return 0;
}
