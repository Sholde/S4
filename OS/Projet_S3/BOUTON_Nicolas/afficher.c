#include <stdio.h>
#include "uvsqgraphics.h"
#include "constantes.h"
#include "gestion_sudoku.h"

void initialiser_fenetre_graphique() {
	init_graphics(LARGEUR,HAUTEUR);
	fill_screen(COUL_FOND);
	affiche_auto_off();
}

void terminer_fenetre_graphique() {
	wait_escape();
}

void quadrillage() {
	
	int i = 0;
	POINT P1, P2;
	

	while(i<10)
	{
		// Horizontale
		P1.x = 0 ; P1.y = TAILLE_CASE*i ;
		P2.x = LARGEUR ; P2.y = TAILLE_CASE*i ;
		draw_line(P1,P2,COUL_TRAIT);
		
		if(i%3 == 0)
		{
			P1.y = P1.y+1; P2.y = P2.y+1;
			draw_line(P1,P2,COUL_TRAIT);
		}
		
		// Verticale
		P1.x = TAILLE_CASE*i ; P1.y = 0 ;
		P2.x = TAILLE_CASE*i ; P2.y = HAUTEUR - TAILLE_CASE;
		draw_line(P1,P2,COUL_TRAIT);
		
		if(i%3 == 0)
		{
			P1.x = P1.x+1; P2.x = P2.x+1;
			draw_line(P1,P2,COUL_TRAIT);
		}
		
		i++;
	}
}

void affiche_val(SUDOKU S) {
	
	int i = 0;
	int j = 0;
	POINT P;
	
	while(j<9)
	{
		if(S.elem[j][i].val != 0)
		{
			// calcul la position d'affichage de l' entier
			P.x = i*TAILLE_CASE + TAILLE_CASE/4;
			P.y = (HAUTEUR - TAILLE_CASE) -(j*TAILLE_CASE);
			
			if(S.elem[j][i].est_travail)
			{
				aff_int(S.elem[j][i].val, TAILLE_POLICE, P, COUL_VAL_TRAVAIL);
			}
			else
			{
				if(S.elem[j][i].est_sol == '1')
				{
					aff_int(S.elem[j][i].val, TAILLE_POLICE, P, COUL_VAL_SOL);
				}
				else
				{
					aff_int(S.elem[j][i].val, TAILLE_POLICE, P, COUL_VAL_DEPART);
				}
			}
		}
		i++;
		if(i>8)
		{
			i = 0;
			j++;
		}
	}
}

void affiche_val_possible(SUDOKU S)
{
	int j = 0;
	int i = 0;
	int cmp = 1;
	POINT P;
	
	while(j<9)
	{
		while(i<9)
		{
			while(cmp<10)
			{
				if(S.elem[j][i].POSSIBLE[cmp] == 1)
				{
					P.x = i*TAILLE_CASE + cmp*(TAILLE_CASE/10);
					P.y = (HAUTEUR - TAILLE_CASE) -(j*TAILLE_CASE);
					aff_int(cmp, TAILLE_POLICE/4, P, COUL_TRAIT);
				}
				cmp++;
			}
			cmp = 1;
			i++;
		}
		i = 0;
		j++;
	}
}

void affiche_nom(char* nom)
{
	POINT P;
	P.x = 0; P.y = HAUTEUR;
	aff_pol(nom, TAILLE_POLICE, P, COUL_TITRE);
}

void affiche_carre_rouge(int j, int i)
{
	POINT bg, hd;
	
	bg.x = i*TAILLE_CASE;
	bg.y = (HAUTEUR - TAILLE_CASE) -((j+1)*TAILLE_CASE);
	
	hd.x = (i+1)*TAILLE_CASE;
	hd.y = (HAUTEUR - TAILLE_CASE) -(j*TAILLE_CASE);
	
	draw_fill_rectangle(bg, hd, COUL_FOND_PB);
	affiche_all();
}

void appelle_acr(SUDOKU S)
{
	int i = 0;
	int j = 0;
	
	while(j < 9)
	{
		while(i < 9)
		{	
			if(S.elem[j][i].est_travail && S.elem[j][i].val == 0)
			{		
				if(verif_val_possible(S,j,i) == 0)
				{
					affiche_carre_rouge(j,i);
				}
			}
			i++;
		}
		i = 0;
		j++;
	}
}

void sudoku_afficher(SUDOKU S, char* nom) {
	
	fill_screen(COUL_FOND);
	affiche_val(S);
	affiche_val_possible(S);
	appelle_acr(S);
	quadrillage();
	affiche_nom(nom);
	affiche_all();
}
