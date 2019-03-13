#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestion_sudoku.h"


SUDOKU lire_fichier (char *nom) {
	SUDOKU S;
	
	FILE* F;
	F = fopen(nom,"r");
	if(!F)
	{
		exit(2);
	}
	
	char s[2]="0";
	char c;
	c = fgetc(F);
	
	int i = 0;
	int j = 0;
	int cmp = 0;
	
	while(c != EOF && j < 9)
	{
		
		if(c != '\0' && c!= '\n')
		{
			i = cmp%9;
			j = cmp/9;
			if(c == '*')
			{
				S.elem[j][i].est_travail = 1;
				c = fgetc(F);
				s[0] = c;
				S.elem[j][i].val = atoi(s);
			}
			else
			{
				if(c == '.')
				{
					S.elem[j][i].val = 0;
					S.elem[j][i].est_travail = 1;
				}
				else
				{
					s[0] = c;
					S.elem[j][i].val = atoi(s);
					S.elem[j][i].est_travail = 0;
				}
			}
			S.elem[j][i].est_sol = '0';
			S = init_tab_vide(S, j, i);
			cmp++;
		}
		c = fgetc(F);
	}
	fclose(F);
	return S;
}

void ecrire_fichier(SUDOKU S, char* nom) {
	
	char* final = malloc(20*sizeof(char));
	
	char a[2];
	a[0] = *(nom+8);
	if(a[0] == 's')
	{
		sprintf(final, "exemple.001.sudoku");
	}
	if(a[0] != 's')
	{
		sprintf(final,"exemple.");
		char b[2];
		b[0] = *(nom+9);
		char c[2];
		c[0] = *(nom+10);
		int entier;
		entier = 100*atoi(a) + 10*atoi(b) + 1*atoi(c) + 1;
		char remp[4];
		if(entier < 100)
		{
			strcat(final,"0");
			if(entier < 10)
			{
				strcat(final,"0");
			}
		}
		sprintf(remp, "%d", entier);
		strcat(final,remp);
		strcat(final,".sudoku");
	}
	
	FILE* F;
	F = fopen(final,"w");
	
	if(!F)
	{
		exit(2);
	}
	
	int i = 0;
	int j = 0;
	char s[2];
	
	while(j < 9)
	{
		
		while(i < 9)
		{
			if(S.elem[j][i].est_travail)
			{
				if(S.elem[j][i].val == 0)
				{
					fprintf(F, ".");
				}
				else
				{
					fprintf(F, "*");
					sprintf(s, "%d", S.elem[j][i].val);
					fprintf(F, s);
				}
			}
			else
			{
				sprintf(s, "%d", S.elem[j][i].val);
				fprintf(F, s);
			}
			i++;
		}
		i = 0;
		j++;
		fprintf(F,"\n");
	}
	fclose(F);
}
