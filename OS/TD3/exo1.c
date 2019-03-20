#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/sysmacros.h>

void affichage_type(const char* path, struct stat statbuf) {
	
	printf("type : ");
	switch(statbuf.st_mode & S_IFMT) {
	case S_IFSOCK : printf("sock\n"); break;
	case S_IFLNK : printf("link\n"); break;
	case S_IFREG : printf("file\n"); break;
	case S_IFBLK : printf("deve\n"); break;
	case S_IFCHR : printf("deve\n"); break;
	case S_IFDIR : printf("repy\n"); break;
	case S_IFIFO : printf("fifo\n"); break;
	}
}

void affichage_permission(const char* path, struct stat statbuf) {
	printf("acces : %lo\n", statbuf.st_mode);
}

void affichage_proprietaire(const char* path, struct stat statbuf) {
	printf("proprietaire : %ld\n", statbuf.st_uid);
}

void affichage_taille(const char* path, struct stat statbuf) {
	printf("taille : %ld\n", statbuf.st_size);
}

int main(int argc, char* argv[]) {
	
	struct stat statbuf;
	const char* path = argv[1];
	
	if(stat(path, &statbuf) == -1)
	{
		printf("error");
		return -1;
	}

	affichage_type(path, statbuf);
	affichage_permission(path, statbuf);
	affichage_proprietaire(path, statbuf);
	affichage_taille(path, statbuf);
	return 0;
}
