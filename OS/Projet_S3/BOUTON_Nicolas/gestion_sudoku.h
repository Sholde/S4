
#ifndef __SUDOKU_H
#define __SUDOKU_H

struct undo {
	int val;
	int i;
	int j;
};

typedef struct undo UNDO;

struct elements {
	int val;
	int est_travail;
	char est_sol;
	int POSSIBLE[10];
};

struct sudoku {
	struct elements elem[9][9];
	UNDO U[100];
	int compteur;
};

typedef struct sudoku SUDOKU;

SUDOKU calcule_val_possible(SUDOKU S, int j, int i);

SUDOKU init_tab_vide(SUDOKU S, int j, int i);

SUDOKU calcule_val_possible_sudoku(SUDOKU S);

int verif_val_possible(SUDOKU S, int j, int i);

int gagne(SUDOKU S);

SUDOKU initialise_undo(SUDOKU S);

SUDOKU implemente_undo(SUDOKU S,int val, int j, int i);

SUDOKU decremente_undo(SUDOKU S);

int compteur_val_possible_case(SUDOKU S, int j, int i);

int compteur_1_val_possible_sudoku(SUDOKU S);

SUDOKU resolution(SUDOKU S);

int prochaine_val_possible(SUDOKU S, int j, int i);

SUDOKU sudoku_modifier_case(SUDOKU S, int j, int i);


#endif
