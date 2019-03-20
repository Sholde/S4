#include <sys/times.h> // times()

#include <unistd.h> // fork()
#include <sys/types.h>
#include <sys/wait.h>

#include <stdlib.h> // exit
#include <stdio.h> // entree sortie

int main (int argc, char** argv) {
	
	struct tms deb, fin;
	int d, f, res = 0;
	if(!fork())
	{
		d = times(&deb);
		system("ls -R -l /bin > poub.txt");
		f = times(&fin);
		res = f - d;
		exit(res);
	}
	
	wait(&res);
	if(WIFEXITED(res))
		printf("%d sec\n", WEXITSTATUS(res));
	return 0;
}
