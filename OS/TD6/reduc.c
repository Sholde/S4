#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/times.h>
#include <string.h>

// Enumération des différents opérateurs possibles
typedef enum {
	OCD_SOMME,
	OCD_MOYENNE,
	OCD_MAX,
	OCD_MIN,
	OCD_TOTAL
} opcode_t;

// Structure contenant les arguments du programme
typedef struct {
	int nbThreads;			//< Nombre de threads à utiliser
	int tailleTableau;		//< Taille du tableau utilisé pour la réduction
	opcode_t code;			//< Opération à réaliser
} arg_t;

// Structure contenant les informations nécessaires au thread
typedef struct {
	int* tab;							//< Tableau d'entiers à traiter
	int indiceDeb;						//< Indice de début de traitement
	int indiceFin;						//< Indice de fin de traitement (non compris)
	int* res;							//< Résultat local
	pthread_t tid;						//< ID thread
	int tPos;							//< Position
	pthread_mutex_t* m;					//< Mutex
} message_t;

// Alias de pointeurs de fonction
typedef int (* ptrVerif) (int *, int, int);

// Fonction thread -- calcule la somme locale d'un tableau
// \param	arg 			Message transmis par le thread père
// \return					NULL
void * sommeTableau (void * arg) {
	message_t* m = (message_t*) arg;
	int i = 0;
	pthread_mutex_lock(m->m);
	for(i = m[0].indiceDeb; i < m[0].indiceFin; i++)
	{
		m[0].res[0] += m[0].tab[i];
	}
	pthread_mutex_unlock(m->m);
	return NULL;
}

// Fin de la réduction -- calcule la somme globale
// \param	msg				Messages issus de l'exécution des threads,
//							contiennent les résultats locaux
// \param	nbThreads		Nombre de threads, et donc de messages
// \return					Résultat global
int reducSomme (message_t * msg, int nbThreads) {
	return msg[0].res[0];
}

// Fonction thread -- calcule la moyenne locale d'un tableau
// \param	arg 			Message transmis par le thread père
// \return					NULL
void * moyenneTableau (void * arg) {
	message_t* m = (message_t*) arg;
	int i = 0;
	pthread_mutex_lock(m->m);
	for(i = m[0].indiceDeb; i < m[0].indiceFin; i++)
	{
		m[0].res[0] += m[0].tab[i];
	}
	m[0].res[0] /= (m[0].indiceFin - m[0].indiceDeb);
	pthread_mutex_unlock(m->m);
	return NULL;
}

// Fin de la réduction -- calcule la moyenne globale
// \param	msg				Messages issus de l'exécution des threads,
//							contiennent les résultats locaux
// \param	nbThreads		Nombre de threads, et donc de messages
// \return					Résultat global
int reducMoyenne (message_t * msg, int nbThreads) {
	return msg[0].res[0];
}

// Fonction thread -- calcule le maximum local d'un tableau
// \param	arg 			Message transmis par le thread père
// \return					NULL
void * maxTableau (void * arg) {
	message_t* m = (message_t*) arg;
	int i = 0;
	pthread_mutex_lock(m->m);
	int max = m[0].res[0];
	for(i = m[0].indiceDeb; i < m[0].indiceFin; i++)
	{
		if(m[0].tab[i] > max)
			m[0].res[0] = m[0].tab[i];
	}
	pthread_mutex_unlock(m->m);
	return NULL;
}

// Fin de la réduction -- calcule le maximum global
// \param	msg				Messages issus de l'exécution des threads,
//							contiennent les résultats locaux
// \param	nbThreads		Nombre de threads, et donc de messages
// \return					Résultat global
int reducMax (message_t * msg, int nbThreads) {
	return msg[0].res[0];
}

// Fonction thread -- calcule le minimum local d'un tableau
// \param	arg 			Message transmis par le thread père
// \return					NULL
void * minTableau (void * arg) {
	message_t* m = (message_t*) arg;
	int i = 0;
	pthread_mutex_lock(m->m);
	int min = m[0].res[0];
	for(i = m[0].indiceDeb; i < m[0].indiceFin; i++)
	{
		if(m[0].tab[i] < min)
			m[0].res[0] = m[0].tab[i];
	}
	pthread_mutex_unlock(m->m);
	return NULL;
}

// Fin de la réduction -- calcule le minimum global
// \param	msg				Messages issus de l'exécution des threads,
//							contiennent les résultats locaux
// \param	nbThreads		Nombre de threads, et donc de messages
// \return					Résultat global
int reducMin (message_t * msg, int nbThreads) {
	return msg[0].res[0];
}

// NE PAS TOUCHER
// Fonction de vérification -- somme des éléments du tableau
// \param	tableau			Tableau d'entiers
// \param	tailleTableau	Taille du tableau d'entiers
// \param	resultat		Résultat obtenu par la réduction
// \return					VRAI si le résultat est juste, FAUX sinon
int verifSomme (int * tableau, int tailleTableau, int resultat) {
	int i, tmp = 0;

	for (i = 0; i < tailleTableau; ++i)
		tmp += tableau [i];

	return resultat == tmp;
}

// NE PAS TOUCHER
// Fonction de vérification -- moyenne des éléments du tableau
// \param	tableau			Tableau d'entiers
// \param	tailleTableau	Taille du tableau d'entiers
// \param	resultat		Résultat obtenu par la réduction
// \return					VRAI si le résultat est juste, FAUX sinon
int verifMoyenne (int * tableau, int tailleTableau, int resultat) {
	int i, tmp = 0;

	if (tailleTableau == 0)
		return resultat == 0;

	for (i = 0; i < tailleTableau; ++i)
		tmp += tableau [i];

	return resultat == (tmp / tailleTableau);
}

// NE PAS TOUCHER
// Fonction de vérification -- maximum du tableau
// \param	tableau			Tableau d'entiers
// \param	tailleTableau	Taille du tableau d'entiers
// \param	resultat		Résultat obtenu par la réduction
// \return					VRAI si le résultat est juste, FAUX sinon
int verifMax (int * tableau, int tailleTableau, int resultat) {
	int i, tmp = 0;

	for (i = 0; i < tailleTableau; ++i)
		tmp = (tmp < tableau [i] ? tableau [i] : tmp);

	return resultat == tmp;
}

// NE PAS TOUCHER
// Fonction de vérification -- minimum du tableau
// \param	tableau			Tableau d'entiers
// \param	tailleTableau	Taille du tableau d'entiers
// \param	resultat		Résultat obtenu par la réduction
// \return					VRAI si le résultat est juste, FAUX sinon
int verifMin (int * tableau, int tailleTableau, int resultat) {
	int i, tmp = 101;

	for (i = 0; i < tailleTableau; ++i)
		tmp = (tmp > tableau [i] ? tableau [i] : tmp);

	return resultat == tmp;
}

// Analyse des arguments du programme. Quitte si le nombre d'arguments est
// différent de 4. Remplit la structure de données des arguments.
// \param	argc			Nombre d'arguments
// \param	argv			Arguments
// \return					Structure de données des arguments
arg_t analyseArguments (int argc, char ** argv) {
	
	if(argc != 4)
		exit(1);
	else
	{
		arg_t a;
		a.nbThreads = atoi(argv[1]);
		a.tailleTableau = atoi(argv[2]);
		if(argv[3][0] == '+')
		{
			a.code = OCD_SOMME;
		}
		else
		{
			if(argv[3][0] == 'm')
			{
				a.code = OCD_MIN;
			}
			else
			{
				if(argv[3][0] == 'M')
				{
					a.code = OCD_MAX;
				}
				else
				{
					if(argv[3][0] == '/')
					{
						a.code = OCD_MOYENNE;
					}
					else
					{
						exit(1);
					}
				}
			}
		}
		return a;
	}
}

// NE PAS TOUCHER
// Récupération de la fonction de vérification à partir de l'opcode
// \param	opcode 			Code de l'opération
// \return					Pointeur de la fonction de vérification
ptrVerif decodeOpcodeVerif (const opcode_t o) {
	switch (o) {
		case OCD_SOMME:		return verifSomme;
		case OCD_MOYENNE:	return verifMoyenne;
		case OCD_MAX:		return verifMax;
		case OCD_MIN:		return verifMin;
		default:
			printf ("L'opération n'a pas été reconnue\n");
			exit (-1);
	}
}

// Génération du tableau avec des entiers compris entre 1 et 100.
// \param	tailleTableau	Taille du tableau d'entiers
// \return					Tableau d'entiers
int * genereTableau (int tailleTableau) {
	
	int* tab = malloc(tailleTableau * sizeof(int));
	srand(times(NULL));
	int i;
	for(i = 0; i < tailleTableau; i++)
	{
		tab[i] = (rand()%100);
	}
	return tab;
}

// Fonction chargée de la réduction multi-threadé, elle va initialiser les
// différentes variables utilisées par les threads (tableau d'entier, messages,
// etc.) puis créer les threads. Une fois l'exécution des threads terminée et
// la réduction opérée, la vérification du résultat est faite.
// \param	arg 			Arguments du programme décodés
void programmePrincipal (const arg_t arg) {
	// Déclaration des variables
	int i, res = 0;
	int * tab;
	message_t* message;
	const int tailleBlock = arg.tailleTableau / arg.nbThreads;
	int* RES;
	pthread_mutex_t m;

	// Allocation de la mémoire
	message = malloc(arg.nbThreads * sizeof(message_t));
	RES = malloc(sizeof(int));
	pthread_mutex_init(&m, NULL);

	// Initialisation des variables et création des threads
	tab = genereTableau(arg.tailleTableau);
	for(i = 0; i < arg.nbThreads; i++)
	{
		message[i].m = &m;
		message[i].tPos = i;
		message[i].tab = tab;
		message[i].res = RES;
		message[i].indiceDeb = i * tailleBlock;
		if(i == arg.nbThreads-1)
		{
			message[i].indiceFin = arg.tailleTableau;
		}
		else
			message[i].indiceFin = message[i].indiceDeb + tailleBlock;
		
		if(arg.code == OCD_SOMME)
			pthread_create(&(message[i].tid), NULL, sommeTableau, &message[i]);
			
		if(arg.code == OCD_MOYENNE)
			pthread_create(&(message[i].tid), NULL, moyenneTableau, &message[i]);
			
		if(arg.code == OCD_MAX)
			pthread_create(&(message[i].tid), NULL, maxTableau, &message[i]);
		
		if(arg.code == OCD_MIN)
			pthread_create(&(message[i].tid), NULL, minTableau, &message[i]);
	}

	// Jointure
	for(i = 0; i < arg.nbThreads; i++)
	{
		pthread_join(message[i].tid, NULL);
	}
	
	// Réduction et affichage du résultat
	if(arg.code == OCD_SOMME)	
	{
		res = reducSomme(message, arg.nbThreads);
		printf("res somme : %d\n", res);
	}
	if(arg.code == OCD_MOYENNE)	
	{
		res = reducMoyenne(message, arg.nbThreads);
		printf("res moyenne : %d\n", res);
	}
	if(arg.code == OCD_MAX)	
	{
		res = reducMax(message, arg.nbThreads);
		printf("res max : %d\n", res);
	}
	if(arg.code == OCD_MIN)	
	{
		res = reducMin(message, arg.nbThreads);
		printf("res min : %d\n", res);
	}
	
	// NE PAS TOUCHER
	if ( (* (decodeOpcodeVerif (arg.code) ) ) (tab, arg.tailleTableau, res) )
		printf ("Le resultat est juste.\n");
	else printf ("Le resultat est faux.\n");
	// FIN

	// Libération de la mémoire
	free(tab);
	free(message);
	pthread_mutex_destroy(&m);
}

// NE PAS TOUCHER
// Fonction main -- analyse les arguments donnés au
// programme, puis exécute le programme principal, chargé de la réduction
// multi-threadée.
// \param	argc			Nombre d'arguments
// \param	argv			Arguments
// \return					Code de retour du programme (0 en cas de réussite)
int main (int argc, char ** argv) {
	arg_t a;

	srand (time (NULL) );

	a = analyseArguments (argc, argv);
	programmePrincipal (a);
	
	return 0;
}
