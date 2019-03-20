#include <sys/times.h> // times()

#include <unistd.h> // fork()
#include <sys/types.h>
#include <sys/wait.h>

#include <stdlib.h> // exit
#include <stdio.h> // entree sortie

int main (int argc, char** argv) {
	
	struct tms time;
	long deb, fin, res;
	deb = times(NULL);
	if(!fork())
	{
		system("ls -R -l /home/user > poub.txt");
		sleep(2);
		exit(0);
	}

	wait(NULL);
	fin = times(&time);
	res = fin - deb;
	printf("Temps processus fils : %ld ** \n", res/sysconf(_SC_CLK_TCK));
	return 0;
}
