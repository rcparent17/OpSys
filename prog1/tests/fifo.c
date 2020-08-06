#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

#define FIFO1 "a"
#define FIFO2 "b"

int main(char* argv[], int argc){
	
	mkfifo(FIFO1, 0666);
	mkfifo(FIFO2, 0666);

	int ogFd = dup(1);

	int pid1 = -1;
	int pid2 = -1;
	int pid3 = -1;
	int pid4 = -1;

	int fdwr1 = -1;
	int fdrd1 = -1;
	int fdwr2 = -1;
	int fdrd2 = -1;

	char* toWrite = "hello world\n";

	// echo > wc > cat
	pid1 = fork();
	if(pid1 == 0){ // same time
		fdwr1 = open(FIFO1, O_WRONLY);
		dup2(fdwr1, 1);
		execlp("echo", "echo", toWrite, NULL); // write fifo1
	}
	else {
		pid2 = fork();
		if(pid2==0){ // same time
			fdwr2 = open(FIFO2, O_WRONLY);
			dup2(fdwr2, 1);
			execlp("wc", "wc", FIFO1, NULL); // read fifo1 && write fifo2
		}
		else{
			pid3 = fork();
			if(pid3 == 0){ // same time
				execlp("cat", "cat", FIFO2, NULL); // read fifo2
			}
			else{
				waitpid(pid3, NULL, 0);
			}
		}
		wait(NULL);
	}
	unlink(FIFO1);
	unlink(FIFO2);
	return 0;
}
