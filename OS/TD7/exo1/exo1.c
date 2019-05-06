#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>

int main (int argc, char** argv) {
	
	pid_t pid;
	char buf[16];
	int pipefd;
	
	if( mkfifo("fic", 0600) == -1 )
	{
		printf("fifo\n");
		return 1;
	}
	
	pid = fork();
	
	if( !pid )
	{
		pipefd = open("fic", O_WRONLY);
		write(pipefd, "Hello world!", 16);
		close( pipefd );
		return 0;
	}
	wait(&pid);
	
	pipefd = open("fic", O_RDONLY);
	read(pipefd, buf, 16);
	close( pipefd );
	
	printf("%s\n", buf);
	
	unlink("fic");
	
	return 0;
}
