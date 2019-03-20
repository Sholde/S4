#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

int dir_ouverture(DIR* D, const char* path) {
	D = opendir(path);
	if(!D)
		return -1;
	return 0;
}

struct dirent* dir_lecture(DIR* D, struct dirent* F, const char* path) {
	F = readdir(D);
	return F;
}

int ecriture(struct dirent* F) {
}

int main(int argc, char* argv[]) {
	
	const char* path = argv[1];
	DIR* D = malloc(sizeof(struct dirent *));
	int r;
	
	r = dir_ouverture(D, path);
	if( r == -1 )
		return 0;
	
	struct dirent* F;
	F = dir_lecture(D, F, path);
	
	
	closedir(D);
	return 0;
}
