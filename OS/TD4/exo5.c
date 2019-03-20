#include <sys/times.h> // times()

#include <unistd.h> // fork()
#include <sys/types.h>
#include <sys/wait.h>

#include <stdlib.h> // exit
#include <stdio.h> // entree sortie

#include <signal.h> // signal kill()

int main (int argc, char** argv) {
	
	int fils = fork();
	if(!fils)
	{
		sleep(1);
		printf("1sec\n");
		sleep(1);
		printf("2sec\n");
		sleep(1);
		printf("3sec\n");
		sleep(1);
		printf("4sec\n");
		sleep(1);
		printf("5sec\n");
		exit(0);
	}
	sleep(3);
	kill(fils, SIGSTOP);
	printf("fils stop\n");
	sleep(5);
	printf("fils cont\n");
	kill(fils, SIGCONT);
	wait(NULL);
	
	return 0;
}
