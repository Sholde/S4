#include <sys/times.h> // times()

#include <stdlib.h> // rand ()

#include <stdio.h> // printf ()

#define infini 100

void init(int** T, int** P, int taille) {
	int i, j;
	for(i = 0; i < taille; ++i)
	{
		for(j = 0; j < taille; ++j)
		{
			T[i][j] = infini;
		}
	}
	
	T[0][1] = 3;
	T[0][5] = 1;
	T[1][2] = 4;
	T[2][1] = -1;
	T[2][3] = 5;
	T[3][5] = 3;
	T[3][6] = 3;
	T[4][0] = 5;
	T[4][5] = 2;
	T[5][2] = 2;
	T[5][0] = 2;
	T[6][3] = -2;
	T[6][4] = 1;
	T[6][5] = 4;
	
	for(i = 0; i < taille; ++i)
	{
		for(j = 0; j < taille; ++j)
		{
			if(T[i][j] != infini)
			{
				P[i][j] = i;
			}
		}
	}
	
	for(i = 0; i < taille; ++i)
	{
		T[i][i] = 0;
		P[i][i] = i;
	}
}

void hash(int** T, int** P, int taille) {
	int i, j, k;
	
	for(k = 0; k < taille; k++)
	{
		for(i = 0; i < taille; i++)
		{
			for(j = 0; j < taille; j++)
			{
				if(T[i][k] != infini && T[k][j] != infini
					&& (T[i][j] > (T[i][k] + T[k][j])) )
				{
					T[i][j] = T[i][k] + T[k][j];
					P[i][j] = k;
				}
				
			}
		}
	}
}

void affichage(int** T, int** P, int taille) {
	int i, j;
	printf("Matrice :\n");
	
	for(i = 0; i < taille; ++i)
	{
		for(j = 0; j < taille; ++j)
		{
			printf("|%3d|", T[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	
	printf("Pere :\n");
	for(i = 0; i < taille; ++i)
	{
		for(j = 0; j < taille; ++j)
		{
			printf("|S%2d|", P[i][j] + 1);
		}
		printf("\n");
	}
	printf("\n");
}

int main () {
	
	srand(times(NULL));
	int taille = 7;
	int** T = malloc(taille * sizeof(int*));
	int** P = malloc(taille * sizeof(int*));
	int i;
	for(i = 0; i < taille; ++i)
	{
		T[i] = malloc(taille * sizeof(int));
		P[i] = malloc(taille * sizeof(int));
	}
		
	init(T, P, taille);
	affichage(T , P, taille);
	hash(T, P, taille);
	affichage(T, P, taille);
	
	for(i = 0; i < taille; ++i)
	{
		free(T[i]);
		free(P[i]);
	}
	free(T);
	free(P);
	return 0;
}
