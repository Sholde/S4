#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct { //graphe représenté par une matrice d'adjacence
  	int nombre_sommet;
  	int ** matrice_adjacence;
} graphe;


void affiche_graphe(graphe G){
	int i,j;
	printf("Graphe avec %d sommets \n",G.nombre_sommet);
	for(i = 0; i<G.nombre_sommet; i++){
		printf("Voisins de %d: ",i);
		for(j = 0; j < G.nombre_sommet; j++){
			if(G.matrice_adjacence[i][j]) printf("%d ",j);
		}
		printf("\n");
	}
}

//Crée le fichier "graphX.pdf" (X = str en param)
//Le fichier n'est généré que si la fonction init_graph est implémentée
void ecrire_fichier_dot(graphe G,char* str){
	if(G.matrice_adjacence == NULL)return;
	FILE* f;
	char buf[64];
	sprintf(buf,"graph%s.dot",str);
	if( !(f = fopen(buf,"w")) ){
		perror("Opening dot file failure\n");exit(2);
	}
	fprintf(f,"graph G { \n");
	for(int i=0;i<G.nombre_sommet;i++){fprintf(f,"%d \n",i);}
	for(int i=0;i<G.nombre_sommet;i++){
		for(int j=0;j<i;j++){
			if(G.matrice_adjacence[i][j]){
				fprintf(f,"%d -- %d\n",i,j);
			}
		}
	}
	fprintf(f,"} \n");
	fclose(f);
	sprintf(buf,"neato -Tpdf graph%s.dot -o graph%s.pdf",str,str);
	system(buf);

}

int degre(graphe G, int i){
	int j;
	int compteur = 0;
	for(j = 0; j<G.nombre_sommet; j++)
		if(j != i)
			compteur = compteur + G.matrice_adjacence[i][j];
	
	return compteur;
}


graphe init_graphe(int n){//créé un graphe dont tous les sommets sont isolés
	graphe G;
	G.nombre_sommet = n;
	G.matrice_adjacence = malloc(n*sizeof(int*));
	int i;
	for(i = 0; i<n; i++)
		G.matrice_adjacence[i] = malloc(n*sizeof(int));
		
	int j;
	for(i = 0; i < n ; i++)
		for(j = 0; j < n ; j++)
			G.matrice_adjacence[i][j] = 0;
	return G;
}

void libere_graphe(graphe G){
	int i;
	for(i = 0; i < G.nombre_sommet; i++)
		free(G.matrice_adjacence[i]);
	free(G.matrice_adjacence);
}

graphe cycle_graphe(int n){//créé un cycle
	graphe G=init_graphe(n);
	int j;
	for(j = 0; j+1 < n ; j++)
		G.matrice_adjacence[j][j+1] = 1;
	G.matrice_adjacence[n-1][0] = 1;
	return G;
}


graphe complet_graphe(int n){//créé un graphe complet
	graphe G=init_graphe(n);
	int i,j;
	for(i = 0; i < n ; i++)
		for(j = 0; j < n; j++)
			if(i != j)
				G.matrice_adjacence[i][j] = 1;
			else 
				G.matrice_adjacence[i][j] = 0;
	return G;
}


graphe alea_graphe(int n, float p){
	graphe G=init_graphe(n);
	
	int i, j, k;
	p = p*1000;
	
	for(i = 0; i < n ; i++)
		for(j = 0; j < n; j++)
			if(i != j)
			{
				k = rand()%1000;
				if(k < p)
					G.matrice_adjacence[i][j] = 1;
			}
	return G;
}

graphe graphe_arbre(int *pere, int n){//créer un arbre couvrant à partir du tableau des pères représenté comme un graphe
	graphe G=init_graphe(n);
	int i,j;
	for(i = 0; i < n ; i++)
		for(j = 0; j < n ; j++)
			if(pere[i] == j)
				G.matrice_adjacence[i][j] = 1;
	return G;
}

void parcours_sommet(graphe G, int s, int *couleur, int *pere){
	int i;
	couleur[s] = 1;
	for(i = 0; i < G.nombre_sommet ; i++)
		if(i != s && couleur[i] == 0 && G.matrice_adjacence[s][i])
		{
			pere[i] = s;
			parcours_sommet(G, i, couleur, pere);
		}
	couleur[s] = 2;
			
}

graphe parcours_graphe(graphe G){
	int i;
	int *couleur = calloc(G.nombre_sommet,sizeof(int)); // 0 est blanc, 1 gris et 2 noir
	
	int *pere = malloc(sizeof(int)*G.nombre_sommet);
	for(i = 0; i < G.nombre_sommet ; i++)
		pere[i] = G.nombre_sommet;
	
	int compteur = 0;
	for(i = 0; i < G.nombre_sommet ; i++)
		if(couleur[i] == 0)
		{
			parcours_sommet(G, i, couleur, pere);
			compteur++;
		}
		
	printf("Nb composantes connexes : %d\n", compteur);
	
	graphe res = graphe_arbre(pere,G.nombre_sommet);
	
	free(couleur);
	free(pere);
	return res;
}


  
void cycle_eulerien(graphe G){//on suppose le graphe connexe
	
}


int main(){
	/* Tests pour vérifier si vos implémentations sont correctes*/
	srand(time(NULL));
  	graphe G = cycle_graphe(10);
  	affiche_graphe(G);
  	ecrire_fichier_dot(G,"Cycle");
	graphe H = complet_graphe(5);
	affiche_graphe(H);
	ecrire_fichier_dot(H,"Complet");
	graphe L = alea_graphe(10,0.2);
	affiche_graphe(L);
	ecrire_fichier_dot(L,"Alea");
	graphe A = parcours_graphe(L);
	affiche_graphe(A);
	ecrire_fichier_dot(A,"Arbre");
	cycle_eulerien(L);
	cycle_eulerien(H);
	libere_graphe(G);
	libere_graphe(H);
	libere_graphe(L);
	libere_graphe(A);
}
