#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#define numForks 69

int main(void){
	float x;
	float y = 0;
	int i;
	for(i = 0; i < numForks; i++){
		if(fork() == 0){
			for(x = 0.1; x < 8000000.0; x += 0.1)
				y = y + 3.14 * 89.64;
		}
		else{
			wait();
		}
	}
	exit();
}
