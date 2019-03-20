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
		for(int i = 0; i < 5; i++)
		{
			sleep(1);
			printf("%d sec\n", i + 1);
		}
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
