#include <stdlib.h>
#include <stdio.h>
#include "uvsqgraphics.h"
#include "constantes.h"
#include "afficher.h"
#include "gestion_sudoku.h"
#include "lire_ecrire.h"

SUDOKU jouer(SUDOKU S, POINT P) {
	
	if(P.y < (HAUTEUR - TAILLE_CASE))
	{
		int ligne = P.x / TAILLE_CASE; // À écrire
		int colonne = (HAUTEUR - TAILLE_CASE - P.y) / TAILLE_CASE; // Car première ligne en haut
		
		if(ligne >= 0 && colonne >= 0) {
			S = sudoku_modifier_case(S,colonne,ligne);
		}
	}
	return S;
}

int test_terminer(SUDOKU S)
{
	if(gagne(S))
	{
		return 1;
	}
	return 0;
}

void verif(int test)
{
	if ( test == 1 )
	{
		printf("GAGNE\n");
	}
	else
	{
		printf("PERDU\n");
	}
}

void termine()
{
	terminer_fenetre_graphique();
	exit(0);
}

void verif_test_termine(SUDOKU S)
{
	int test;
	test = test_terminer(S);
	verif(test);
	termine();
}

SUDOKU action(SUDOKU S, char* nom)
{
	int a = 0; char c; POINT P; int f;
	
	while (gagne(S) == 0)
	{
		a = wait_key_arrow_clic(&c,&f,&P);
		if(a == EST_CLIC)
		{
			S = jouer(S, P);
			S = calcule_val_possible_sudoku(S);
			sudoku_afficher(S, nom);
		}
		else
		{
			if(a == EST_TOUCHE)
			{
				if(c == 'U')
				{
					S = decremente_undo(S);
					S = calcule_val_possible_sudoku(S);
					sudoku_afficher(S, nom);
				}
				if(c == 'V')
				{
					S = resolution(S);
					S = calcule_val_possible_sudoku(S);
					sudoku_afficher(S, nom);
					
					verif_test_termine(S);
				}
				if(c == 'S')
				{
					ecrire_fichier(S, nom);
				}
				if(c == 'Q')
				{
					printf("Vous avez quitté\n");
					termine();
				}
			}
		}
	}
	return S;
}

SUDOKU initialise(SUDOKU S, char* nom)
{
	S = lire_fichier(nom);
	S = calcule_val_possible_sudoku(S);
	S = initialise_undo(S);
	
	initialiser_fenetre_graphique();
	sudoku_afficher(S, nom);
	return S;
}

int main (int argc, char *argv[]) {
	
	SUDOKU S;
	S = initialise(S,argv[1]);

	S = action(S, argv[1]);
	
	verif_test_termine(S);
}
