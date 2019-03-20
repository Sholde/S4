#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>

#include <time.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	
	int i, k;
	
	srand(time(NULL));
	
	for(i = 0; i < 10; i++)
	{
		if(!fork())
		{
			k = rand()%10 + 1;
			sleep(k);
			printf("(fils) Mon PID : %d\n", getpid());
			exit(0);
		}
	}
	
	for(i = 0; i < 10; i++)
	{
		k = wait(NULL);
		printf("%d est fini\n", k);
	}
	return 0;

}
