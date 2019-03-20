#include "se_fichier.c"
#include "se_fichier.h"

int main() {
	SE_FICHIER F;
	F = SE_ouverture("/tmp/salut", 0666);
	
	int b;
	b = SE_ecritureCaractere(F, 'e');
	
	int a;
	a = SE_fermeture(F);
	return 0;
}
