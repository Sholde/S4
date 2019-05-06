#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int* nb_exec;
	int id;
	int n;
	pthread_mutex_t * m;
	pthread_cond_t * c;
	pthread_t tid;
} arg_t;

void barrier (arg_t* A) {

	pthread_mutex_lock(A->m);
	(*(A->nb_exec))++;
	if(*(A->nb_exec) < (A->n))
	{
		printf("%d attends\n\n", A->id);
		pthread_cond_wait (A->c, A->m);
	}
	else
	{
		printf("%d libère tous le monde\n\n",A->id);
		for (int i = 0; i < *(A->nb_exec) - 1; i++)
		{
			pthread_cond_signal (A->c);
		}
		*(A->nb_exec) = 0;
	}
	pthread_mutex_unlock(A->m);
}

void* func (void* arg) {
	arg_t* A = (arg_t*) arg;
	
	printf("%d commence\n", A->id);
	
	barrier(A);
	printf("salut c'est %d\n", A->id);
	
	barrier(A);
	printf("salut c'est %d\n", A->id);
	return NULL;
}

int main (int argc, char** argv) {
	
	int n = atoi(argv[1]);
	arg_t A[n];
	int nb_exec = 0;
	
	pthread_mutex_t m;
	pthread_cond_t c;
	pthread_t tid[n];
	
	printf ("\nHello World!\n\n");
	
	pthread_mutex_init (&m, NULL);
	pthread_cond_init (&c, NULL);
	
	for (int i = 0; i < n; i++)
	{
		A [i] .nb_exec = &nb_exec;
		A [i] .id = i;
		A [i] .n = n;
		A [i] .m = &m;
		A [i] .c = &c;
		A [i] .tid = tid [i];
		pthread_create (&(A [i] .tid), NULL, func, &(A [i]) );
	}
	
	for (int i = 0; i < n; i++)
	{
		pthread_join (A [i] .tid, NULL);
	}
	
	printf ("\n");
	
	pthread_cond_destroy (&c);
	pthread_mutex_destroy (&m);
	return 0;
}
