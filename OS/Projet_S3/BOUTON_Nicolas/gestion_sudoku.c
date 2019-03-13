#include <stdlib.h>
#include <stdio.h>
#include "gestion_sudoku.h"
#include "afficher.h"
#include "constantes.h"
#include "afficher.h"


SUDOKU init_tab_vide(SUDOKU S, int j, int i)
{
	int indice = 0;
	while(indice<10)
	{
		S.elem[j][i].POSSIBLE[indice] = 0;
		indice++;
	}
	return S;
}

SUDOKU calcule_val_possible_case(SUDOKU S, int j, int i) {
	
	int ligne_colonne = 0;
	int tmp_l = (i/3)*3;
	int tmp_c = (j/3)*3;
	int cmp = 1;
	
	S = init_tab_vide(S,j,i);
	S.elem[j][i].POSSIBLE[0] = 1;
	
	while(cmp<10)
	{
		while(ligne_colonne<9 && (cmp != S.elem[j][ligne_colonne].val) && (cmp != S.elem[ligne_colonne][i].val) && (cmp != S.elem[tmp_c+ligne_colonne/3][tmp_l+ligne_colonne%3].val))
		{
			ligne_colonne++;
		}
		if(ligne_colonne>8)
		{
			S.elem[j][i].POSSIBLE[cmp] = 1;
		}
		
	ligne_colonne = 0;
	cmp++;
	}
	return S;
}

int verif_val_possible(SUDOKU S, int j, int i)
{
	int cmp = 1;
	
	while(cmp<10)
	{
		if(S.elem[j][i].POSSIBLE[cmp])
		{
			return 1;
		}
		cmp++;
	}
	return 0;
}

SUDOKU calcule_val_possible_sudoku(SUDOKU S)
{
	int i = 0;
	int j = 0;
	
	while(j<9)
	{
		while(i<9)
		{
			if(S.elem[j][i].est_travail)
			{
				S = calcule_val_possible_case(S,j,i);
			}
			else
			{
				init_tab_vide(S,j,i);
			}
			i++;
		}
		i = 0;
		j++;
	}
	return S;
}

int gagne(SUDOKU S)
{
		int i = 0;
		int j = 0;
		int cmp = 1;
		
		while(j < 9)
		{
			while(i < 9)
			{
				while(cmp < 10)
				{
					if(S.elem[j][i].val == 0)
					{
						return 0;
					}
					cmp++;
				}
				cmp = 1;
				i++;
			}
			i = 0;
			j++;
		}
		return 1;
}

int prochaine_val_possible(SUDOKU S, int j, int i)
{
	int cmp = S.elem[j][i].val;
	cmp++;
	int stop = 0;
	
	// %10 car 10 val dans possible
	while(stop < 20 && S.elem[j][i].POSSIBLE[cmp%10] != 1)
	{
		cmp++;
		stop++;
	}
	if(stop >= 20)
	{
		printf("probleme val \n");
		exit(1);
	}
	return cmp%10;
}

SUDOKU sudoku_modifier_case(SUDOKU S, int j, int i) {
	
	if(S.elem[j][i].est_travail)
	{
		S.elem[j][i].val = prochaine_val_possible(S,j,i);
		S = implemente_undo(S, S.elem[j][i].val, j, i);
	}
	return S;
}

SUDOKU initialise_undo(SUDOKU S)
{
	int cmp = 0;
	while(cmp < TAILLE_UNDO)
	{
		S.U[cmp].val = 0;
		S.U[cmp].i = 0;
		S.U[cmp].j = 0;
		cmp++;
	}
	S.compteur = 0;
	return S;
}

SUDOKU implemente_undo(SUDOKU S,int val, int j, int i)
{
	if(S.compteur < TAILLE_UNDO-1)
	{
		S.U[S.compteur].val = val;
		S.U[S.compteur].i = i;
		S.U[S.compteur].j = j;
		S.compteur++;
	}
	return S;
}

SUDOKU decremente_undo(SUDOKU S)
{
	if(S.compteur > 0)
	{
		S.compteur--;
		int i = S.U[S.compteur].i;
		int j = S.U[S.compteur].j;
		int val = S.U[S.compteur].val;
		val--;
		if(val < 0)
		{
			val = 9;
		}
		
		S.elem[j][i].val = 0;
		S = calcule_val_possible_case(S, j, i);

		int cmp = 0;
		
		while(cmp < 20 && S.elem[j][i].POSSIBLE[val] == 0)
		{
			cmp++;
			val--;
			if(val < 0)
			{
				val = 9;
			}
		}
		
		S.elem[j][i].val = val;
		
		S.U[S.compteur].val = 0;
		S.U[S.compteur].i = 0;
		S.U[S.compteur].j = 0;
	}
	return S;
}

int compteur_val_possible_case(SUDOKU S, int j, int i)
{
	int cmp = 1;
	int res = 0;
	
	while(cmp < 10)
	{
		res += S.elem[j][i].POSSIBLE[cmp]; // car soit 0 soit 1 et if implicite
		cmp++;
	}
	return res;
}

int compteur_1_val_possible_sudoku(SUDOKU S)
{
	int i = 0;
	int j = 0;
	
	while(j < 9)
	{
		while(i<9)
		{
			if(compteur_val_possible_case(S, j, i) == 1)
			{
				return 1;
			}
			i++;
		}
		i = 0;
		j++;
	}
	return 0;
}

SUDOKU resolution(SUDOKU S)
{
	int i = 0;
	int j = 0;
	int tour = 0;
	
	while(tour < 10)
	{
		while(j < 9)
		{
			while(i < 9)
			{
				if(S.elem[j][i].est_travail)
				{
					if(S.elem[j][i].val == 0 && compteur_val_possible_case(S,j,i) == 1)
					{
						S.elem[j][i].val = prochaine_val_possible(S,j,i);
						if(S.elem[j][i].val == 0)
						{
							S.elem[j][i].val = prochaine_val_possible(S,j,i);
						}
						
						S.elem[j][i].est_travail = 0;
						S.elem[j][i].est_sol = '1';
						S = init_tab_vide(S,j,i);
						
						S = calcule_val_possible_sudoku(S);
					}
				}
				i++;
			}
			i = 0;
			j++;
		}
		i = 0;
		j = 0;
		tour++;
	}
	
	
	return S;
}
