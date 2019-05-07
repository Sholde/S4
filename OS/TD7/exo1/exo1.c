#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>

#define succes 0
#define error_fic 1

int main (int argc, char** argv) {
	
	pid_t pid;
	char buf[16];
	int pipefd;
	
	if( mkfifo("fic", O_CREAT) == -1 )
	{
		printf("error : mkfifo\n");
		return error_fic;
	}
	
	pid = fork();
	
	if( !pid )
	{
		pipefd = open("fic", O_WRONLY);
		write(pipefd, "Hello world!", 16);
		close( pipefd );
		return succes;
	}
	else 
	{
		wait(&pid);
		
		pipefd = open("fic", O_RDONLY);
		read(pipefd, buf, 16);
		close( pipefd );
		
		printf("%s\n", buf);
		
		unlink("fic");
		
		return succes;
	}
}
