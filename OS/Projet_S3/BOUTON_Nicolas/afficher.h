#include "gestion_sudoku.h"

#ifndef __AFFICHER_H
#define __AFFICHER_H
// Fonction a appeler au début poour créer la fenêtre grapĥique
void initialiser_fenetre_graphique();

// Fonction a appeler à la fin poour terminer proprement la fenêtre grapĥique
void terminer_fenetre_graphique();

// Fonction qui affiche l'état courant du sudoku
void sudoku_afficher(SUDOKU S, char* nom);

// Fonction qui affiche le quadrillage
void quadrillage();

// Fonction qui affiche les valeurs
void affiche_val(SUDOKU S);

void affiche_val_possible(SUDOKU S);

void affiche_nom(char* nom);

void affiche_carre_rouge(int j, int i);
#endif
