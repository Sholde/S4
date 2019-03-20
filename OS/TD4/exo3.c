#include <stdio.h> // entree sortie

#include <unistd.h> // fork
#include <sys/types.h>
#include <sys/wait.h>

#include <stdlib.h> // exit

void petit_1( int m, int n) {
	int i, iter = m * n;
	for(i = 0; i < iter; i++)
	{
		if(!fork())
		{
			exit(1);
		}
	}
	int a = 0, b;
	for(i = 0; i < iter; i++)
	{
		wait(&b);
		a += WEXITSTATUS(b);
	}
	printf("pere : %d\n", a);
}

void petit_2 ( int m, int n ) {
	int i, j, a, b;
	for(i = 0; i < m; i++)
	{
		if(!fork())
		{
			for(j = 0; j < n; j++)
			{
				if(!fork())
				{
					exit(1);
				}
			}
			a = 0;
			for(j = 0; j < n; j++)
			{
				wait(&b);
				a += WEXITSTATUS(b);
			}
			printf("fils : %d\n", a);
			exit(a);
		}
	}
	a = 0;
	for(i = 0; i < m; i++)
	{
		wait(&b);
		a += WEXITSTATUS(b);
	}
	printf("pere : %d\n", a);
}

void petit_3 ( int m, int n) {
	int j;
	for(j = 0; j < n; j++)
	{
		if(!fork())
		{
			printf("mon pid : %d\n", getpid());
			exit(0);
		}
	}
	exit(0);
}

int main () {
	
	printf("\nPetit 1 :\n");
	petit_1( 2, 4);
	printf("\nPetit 2 :\n");
	petit_2( 2, 4);
	printf("\nPetit 3 :\n");
	//petit_3( 2, 4);
	return 0;
}
