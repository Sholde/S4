#include "se_fichier.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

SE_FICHIER SE_ouverture (const char * chemin, int acces) {
	SE_FICHIER F;
	F.chemin = chemin;
	F.acces = acces;
	F.descripteur = open(F.chemin, F.acces);
	if(F.descripteur == -1)
	{
		F.descripteur = creat(F.chemin, F.acces);
		F.descripteur = open(F.chemin, F.acces);
	}
	return F;
}

int SE_fermeture (SE_FICHIER fichier) {
	return close(fichier.descripteur);
}

int SE_suppression (const char * chemin) {
	return unlink(chemin);
}

int SE_lectureCaractere (SE_FICHIER fichier,char * caractere) {
	return read(fichier.descripteur, caractere, 1);
}

int SE_ecritureCaractere (SE_FICHIER fichier,const char caractere) {
	if((fichier.acces > 6) & 1 == 0)
	{
		return -1;
	}
	int fd1, fd2;
	fd1 = lseek(fichier.descripteur, 0, SEEK_END);
	fd2 = write(fichier.descripteur, &caractere, 1);
	return (fd1 != 0) && (fd2 != 0);
}

int SE_lectureChaine (SE_FICHIER fichier, char * chaine, int tailleMax){
	int i = 0;
	char c;
	
	if(SE_lectureCaractere(fichier, &c) == -1)
		return -1;
	
	while(c != '\0' && c != '\n' && i<tailleMax)
	{
		chaine[i] = c;
		if(SE_lectureCaractere(fichier, &c) == -1)
			return -1;
		i++;
	}
	
	if(c != '\0' || c != '\n')
		return i;
	
	return 0;
}

int SE_ecritureChaine (SE_FICHIER fichier, const char * chaine, int taille) {
	int i = 0;
	char c;
	
	while(i<taille)
	{
		c = chaine[i];
		if(SE_ecritureCaractere(fichier, c) == -1)
			return -1;
		i++;
	}
	return i;
}

int SE_lectureEntier (SE_FICHIER fichier, int * entier) {
	return 0;
}
	
int SE_ecritureEntier (SE_FICHIER fichier, const int entier) {
	return 0;
}
