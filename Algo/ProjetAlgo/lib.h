
typedef struct l{ //graphe représenté par une liste d'adjacence
  	int voisin;
  	int poids;
    struct l* suiv; // pointe vers prochine val
} liste; // liste des voisin

typedef struct { //graphe représenté par une liste d'adjacence
  	liste** list; //pointe vers 100 liste 
} graphe;
