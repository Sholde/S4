#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Struct thread
typedef struct art{
	int* nb_exec;				//< compte le nb de thread qui ont commencé à s'excécuter
	int entier;					//< entier à envoyer
	int id;						//< id du thread
	int max;					//< nb de thread
	int* deb;					//< id de l'envoyeur
	int* fin;					//< id du destinateur
	char* found;					//< indique si le detinataire a recu le message
	
	struct art* left;				//< voisin de gauche
	struct art* right;				//< voisin de droite
	
	pthread_mutex_t* m;			//< mutex
	pthread_cond_t* c;			//< cond
} arg_t;

// Attends tous les threads puis continu
void barrier (arg_t* A) {
	
	pthread_mutex_lock (A->m);
	(*A->nb_exec)++;
	
	if(*(A->nb_exec) < (A->max))
	{
		pthread_cond_wait (A->c, A->m);
	}
	else
	{
		for (int i = 0; i < *(A->nb_exec) - 1; i++)
		{
			pthread_cond_signal (A->c);
		}
		*A->nb_exec = 0;
	}
	pthread_mutex_unlock (A->m);
}

// init les threads
void initThread (arg_t* A) {
	
	pthread_mutex_lock (A->m);
	(*A->nb_exec)++;
	
	if(*A->nb_exec == 1)
	{
		srand( time(NULL) );
		A->entier = rand() % 100 + 1;
		*A->deb = A->id;
	}
	if(*A->nb_exec == A->max)
	{
		*A->fin = A->id;
	}
	
	pthread_mutex_unlock (A->m);
}

void verifEnd (arg_t* A) {
	pthread_mutex_lock (A->m);
	
	if( A->id == *A->fin )
	{
		if( A->entier != 0 )
		{
			*A->found = 1;
		}
	}
	
	pthread_mutex_unlock (A->m);
}

// envoie entier
void sendInt (arg_t* A) {

	pthread_mutex_lock (A->m);

	if(A->entier != 0)
	{
		if(A->id > *A->fin)
		{
			A->left->entier = A->entier;
			A->entier = 0;
		}
		else
		{
			A->right->entier = A->entier;
			A->entier = 0;
		}
	}
	
	pthread_mutex_unlock (A->m);
}


// Thread
void* func (void* arg) {
	arg_t* A = (arg_t*) arg;
	
	initThread (A);
	barrier (A);
	
	verifEnd (A);
	barrier (A);
	
	//~ sendInt (A);
	//~ barrier (A);
	
	return NULL;
}

// Main
int main () {
	int n = 10;
	arg_t A [n];
	int nb_exec = 0, deb = 0, fin = n-1;
	char found = 0;
	
	pthread_mutex_t m;
	pthread_cond_t c;
	pthread_t tid [n];
	
	pthread_mutex_init (&m, NULL);
	pthread_cond_init (&c, NULL);
	
	for (int i = 0; i < n; i++)
	{
		A [i] .entier 	= 0;
		A [i] .nb_exec 	= &nb_exec;
		A [i] .id 		= i;
		A [i] .max		= n;
		A [i] .deb 		= &deb;
		A [i] .fin 		= &fin;
		A [i] .m 		= &m;
		A [i] .c 		= &c;
		A [i] .found 	= &found;
		
		if(i == 0)
			A [i] .left = NULL;
		else
			A [i] .left = &(A [i-1]);
			
		if(i == n-1)
			A [i] .right = NULL;
		else
			A [i] .right = &(A [i+1]);
		
		pthread_create (&(tid [i]), NULL, func, &(A [i]) );
	}
	
	for (int i = 0; i < n; i++)
	{
		pthread_join (tid [i], NULL);
	}
	
	printf ("sender   : %d\n", *A [0] .deb);
	printf ("adressee : %d\n",*A [0] .fin);
	printf ("integer  : %d\n", A [*A [0] .fin] .entier);
	
	pthread_cond_destroy (&c);
	pthread_mutex_destroy (&m);
	
	return 0;
}
