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
	printf("dad created %d child\n", a);
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
			printf("child created %d child\n", a);
			exit(1);
		}
	}
	a = 0;
	for(i = 0; i < m; i++)
	{
		wait(&b);
		a += WEXITSTATUS(b);
	}
	printf("dad created %d child\n", a);
}

int petit_3 ( int m, int n) {
	int j, v, k = 0;
	for(j = 0; j < n; j++)
	{
		v = fork();
	}
	if(!v)
	{
		exit(1);
	}
	
	for(v = 0, j = 0; j < n; j++)
	{
		wait(&k);
		v += k;
	}
	printf(" nb = %d\n", v);
	exit(v);
}

int main () {
	
	int m = 2, n = 4;
	printf("\nPetit 1 :\n");
	petit_1( m, n);
	printf("\nPetit 2 :\n");
	petit_2( m, n);
	printf("\nPetit 3 :\n");
	m = petit_3( m, n);
	return 0;
}
