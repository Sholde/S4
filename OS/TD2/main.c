#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "se_fichier.h"
#include "se_fichier.c"

// Affichage du contenu d'un fichier
// \param	chemin			Nom/chemin du fichier à afficher
// \return					-1 si échec à l'ouverture, 0 sinon
int affichage (const char * chemin) {  
	SE_FICHIER F;
	F.acces = 0666;
	F = SE_ouverture(chemin, F.acces);
	if(F.descripteur == -1) { return -1; }

	char c;
	
	while(SE_lectureCaractere(F, &c))
	{
		write(1, &c, 1);
	}
	
	SE_fermeture(F);
	return 0;
}
// Copie de fichier
// \param	chemin1			Nom/chemin du fichier source
// \param	chemin2			Nom/chemin du fichier destination
// \return					-1 si échec à l'ouverture, 0 sinon
int copie (const char * chemin1, const char * chemin2) {
	SE_FICHIER F1,F2;
	F1.acces = F2.acces = 0666;
	F1 = SE_ouverture(chemin1, F1.acces);
	F2 = SE_ouverture(chemin2, F2.acces);
	
	if(F1.descripteur == -1 || F1.descripteur == -1)
		return -1;
	
	char c;
	
	while(SE_lectureCaractere(F1, &c))
	{
		write(F2.descripteur, &c, 1);
	}
	
	SE_fermeture(F1);
	SE_fermeture(F2);
	return 0;
}
// Déplacement de fichier
// \param	chemin1			Nom/chemin du fichier source
// \param	chemin2			Nom/chemin du fichier destination
// \return					-1 si échec à l'ouverture, 0 sinon
int deplacement (const char * chemin1, const char * chemin2) {
	copie(chemin1, chemin2);
	SE_FICHIER F1;
	F1.acces = 0666;
	F1 = SE_ouverture(chemin1, F1.acces);
	
	if(F1.descripteur == -1)
		return -1;
	
	SE_suppression(F1.chemin);
	
	SE_fermeture(F1);
	return 0;
}
// Comparaison entre deux fichiers
// \param	chemin1			Nom/chemin du premier fichier
// \param	chemin2			Nom/chemin du second fichier
// \return					-1 si échec à l'ouverture,
//							1 si fichiers identiques, 0 sinon
int sontIdentiques (const char * chemin1, const char * chemin2) {
	SE_FICHIER F1,F2;
	F1.acces = F2.acces = 0666;
	F1 = SE_ouverture(chemin1, F1.acces);
	F2 = SE_ouverture(chemin2, F2.acces);
	
	if(F1.descripteur == -1 || F1.descripteur == -1)
		return -1;
	
	char c1,c2;
	
	while(SE_lectureCaractere(F1, &c1) && SE_lectureCaractere(F2, &c2))
	{
		if(c1 != c2)
		 return 0;
	}
	if(SE_lectureCaractere(F1, &c1) || SE_lectureCaractere(F2, &c2))
	{
		return 0;
	}
	
	SE_fermeture(F1);
	SE_fermeture(F2);
	return 1;
}

void verifAffichage () {
	int nstdout = creat ("test2.txt", 0644);
	int tmp, tmp2;

	system ("echo 'This file\nis\n\nGREAT!\n' >test1.txt");

	tmp = dup (fileno (stdout) );

	// Vider (entre autre) le buffer de stdout
	fflush (NULL);
	dup2 (nstdout, fileno (stdout) );

	affichage ("test1.txt");

	// Vider (entre autre) le buffer de stdout
	fflush (NULL);
	dup2 (tmp, fileno (stdout) );

	close (nstdout); close (tmp);

	if (! system ("diff test1.txt test2.txt >diff.log") )
		printf ("'affichage()' test has succeeded.\n");
	else
		printf ("'affichage()' test has failed.\n");

	system ("rm -f diff.log test1.txt test2.txt");
}

void verifCopie () {
	system ("echo 'This file\nis\n\nGREAT!\n' >test1.txt");

	copie ("test1.txt", "test2.txt");

	if (! system ("diff test1.txt test2.txt >diff.log") )
		printf ("'copie()' test has succeeded.\n");
	else
		printf ("'copie()' test has failed.\n");

	system ("rm -f diff.log test1.txt test2.txt");
}

void verifDeplacement () {
	system ("echo 'This file\nis\n\nGREAT!\n' >test1.txt");
	system ("cat test1.txt >test2.txt");

	deplacement ("test2.txt", "test3.txt");

	if (! system ("test -e test2.txt") )
		printf ("'deplacement() test has failed.\n");
	else if (! system ("diff test1.txt test3.txt >diff.log") )
		printf ("'deplacement()' test has succeeded.\n");
	else
		printf ("'deplacement()' test has failed.\n");

	system ("rm -f diff.log test1.txt test3.txt");
}

void verifSontIdentiques () {
	system ("echo 'This file\nis\n\nGREAT!\n' >test1.txt");
	system ("echo 'This file\nis\n\nGREAT!\n' >test2.txt");
	system ("echo 'This file\nis\n\nGREAT!\n\n' >test3.txt");
	system ("echo 'This fil\nis\n\nGREAT!\n' >test4.txt");
	system ("echo 'This file\nis\nGREAT!\n' >test5.txt");

	if (! sontIdentiques ("test1.txt", "test2.txt") )
		printf ("'sontIdentiques()' test#1 has failed.\n");
	else if (sontIdentiques ("test1.txt", "test3.txt") )
		printf ("'sontIdentiques()' test#2 has failed.\n");
	else if (sontIdentiques ("test2.txt", "test4.txt") )
		printf ("'sontIdentiques()' test#3 has failed.\n");
	else if (sontIdentiques ("test3.txt", "test5.txt") )
		printf ("'sontIdentiques()' test#4 has failed.\n");
	else
		printf ("'sontIdentiques()' test has succeeded.\n");

	system ("rm -f test1.txt test2.txt test3.txt test4.txt test5.txt");
}

int main (int argc, char ** argv) {
	verifAffichage ();
	verifCopie ();
	verifDeplacement ();
	verifSontIdentiques ();

	return 0;
}
