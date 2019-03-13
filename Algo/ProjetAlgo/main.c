#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "lib.h"

// init variable
#define TAILLE_GRAPHE 100
#define nbTier1 8
#define nbTier2 20
#define nbTier3 72
#define ZERO 0

#define poidsMaxTier1 10
#define poidsMinTier1 5
#define poidsMaxTier2 20
#define poidsMinTier2 10
#define poidsMaxTier3 50
#define poidsMinTier3 15

void affiche_graphe(graphe G){
	int i, j;
	graphe tmp; // pour pouvoir parcourir la liste sans y toucher reelment(car pointeur)
	tmp.list = G.list;
	for(i = 0; i < TAILLE_GRAPHE; i++)
	{
		
		if(tmp.list[i] != NULL)
		{
			printf("Voisins de %d : \n", i);
			
			for(j = 0; tmp.list[i]!= NULL && j < TAILLE_GRAPHE; j++)
			{
				printf("(s : %d, p : %d) ", tmp.list[i]->voisin, tmp.list[i]->poids);
				tmp.list[i] = tmp.list[i]->suiv;
			}
			
			printf("\n");
		}
	}
}

graphe init_graphe(int n){
	graphe G;
	G.list = malloc( TAILLE_GRAPHE * sizeof(liste*) );//init juste liste de 100 lister
	
	int i;
	for(i = 0; i < TAILLE_GRAPHE; i++) // ini toute les liste de voisin a NULL
	{
		G.list[i] = NULL;
	}
	return G;
}

liste* insere_debut(liste* L, int voisin, int poids)
{
	liste* lres;
	lres = malloc(sizeof(liste));
	if( lres == NULL){
		fprintf(stderr,"ERREUR: echec malloc\n");
		exit(EXIT_FAILURE);
	}
	lres->voisin = voisin;
	lres->poids = poids;
	lres->suiv = L;
	/*L = lres;
	  return l;*/
	return lres;
}

graphe backbone(graphe G, float p, int deb, int fin, int poids_min, 
	int poids_max){
	
	graphe tmp;
	tmp.list = G.list;
	
	int i, j, k;
	p = p*1000;
	
	for(i = deb; i < fin ; i++)
	{
		for(j = deb; j < fin; j++)
		{
			if(i != j)
			{
				k = rand()%1000;
				if(k < p)
				{
					k = rand()%(poids_max - poids_min) + poids_min;
					tmp.list[i] = insere_debut(tmp.list[i], j, k);
				}
			 }
		 }
	 }
	return tmp;
}

graphe autreTier(graphe G, int debTierPrec, int finTierPrec, int deb, int fin, 
	int poids_min, int poids_max, float probaPrec, float probaCur) {
		
	graphe tmp;
	tmp.list = G.list;
	
	return tmp;
}

graphe calcul(graphe G) { // juste pour tester
	
	G = backbone(G, 0.75, ZERO, nbTier1, poidsMinTier1, poidsMaxTier1);

	//~ int k;
	//~ k = alea
	
	//~ G = alea_graphe(G, 0.75, nbTier1, nbTier1 + nbTier2, poidsMinTier2, 
		//~ poidsMaxTier2, 2);
		
	//~ G = alea_graphe(G, 0.75, nbTier1 + nbTier2, TAILLE_GRAPHE, poidsMinTier3, 
		//~ poidsMaxTier3);
		
	return G;
}

void libere_graphe(graphe G){
	
	int i, j;
	liste* pointeur = NULL;// juste pour simplifier
	
	for(i = 0; i < TAILLE_GRAPHE; i++)
	{
		pointeur = G.list[i];
		for(j = 0; pointeur != NULL && j < TAILLE_GRAPHE; j++)
		{
			G.list[i] = pointeur;
			free(pointeur);
			pointeur = G.list[i]->suiv;
		}
	}
	free(G.list);
}

int main(){
	// Test
	
	srand(time(NULL));
	
	graphe G = init_graphe(TAILLE_GRAPHE);
	G = calcul(G);
	affiche_graphe(G);
	libere_graphe(G);
	
	return 0;
}
