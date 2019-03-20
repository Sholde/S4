#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>

#include <time.h>
#include <stdlib.h>

int main() {
	int r = 0, p = 0, k = 0 , v;
	srand(time(NULL));
	v = fork();
	
	if(!v)
	{
		r = getpid();
		p = getppid();
		printf("fils : Hello World!\n");
		printf("Mon PID est %d et celui de mon pere est %d !\n", r, p);
		
		k = rand()%49 + 1;
		printf("nb aleatoire fils : %d\n", k);
		exit(k);
	}
	
	else
	{
		int retk = -1;
		waitpid(-1, &retk, 0);
		if(WIFEXITED(retk))
			retk = WEXITSTATUS(retk);
		r = getpid();
		printf("pere : Hello World!\n");
		printf("Mon PID est %d et celui de mon fils est %d !\n", r, v);
		printf("nb aleatoire pere : %d\n", retk);
		return 0;
	}
}
