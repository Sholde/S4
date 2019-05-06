
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

void verifArg (int argc) {
	if( argc != 2 )
	{
		exit(0);
	}
}

int main (int argc, char** argv) {
	
	verifArg (argc);
	
	int number = atoi (argv[1]);
	
	pid_t pid[number];
	int pipefd[number + 1][2];
	for(int i = 0; i < number+1; i++)
	{
		pipe( pipefd[i] );
	}
	
	for(int i = 0; i < number; i++)
	{
		pid[i] = fork();
		if( !pid[i] )
		{
			printf("pid : %d\n", getpid());
			srand( getpid() );
			
			int timeWait = rand() % 10 + 1 ;
			printf("wait : %d\n", timeWait);
			
			sleep( timeWait );
			
			// Barrier
			int myId = getpid();
			write(pipefd[0][1], NULL, sizeof(int) );
			
			read(pipefd[i+1][0], NULL, sizeof(int) );
			
			printf("%d\n", i);
			return 0;
		}
	}
	
	for(int i = 1; i < number+1; i++)
	{
		read(pipefd[0][0], NULL, sizeof(int) );
	}
	
	printf("dad has finished to read\n");
	
	for(int i = 1; i < number+1; i++)
	{
		write(pipefd[i][1], NULL, sizeof(int) );
	}
	
	for(int i = 0; i < number; i++)
	{
		wait(NULL);
	}
	printf("end of processus\n");
	
	return 0;
}
